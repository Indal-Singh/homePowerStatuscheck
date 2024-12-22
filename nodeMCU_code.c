#include <ESP8266WiFi.h>
#include <ArduinoWebsockets.h>

const char* ssid = "Indal Singh";
const char* password = "987654321";
const char* websocketServer = "ws://test.raagdhun.in";

using namespace websockets;

WebsocketsClient client;

const int ledPin = D0; // GPIO pin for LED

void setup() {
    Serial.begin(115200);

    // Connect to WiFi
    WiFi.begin(ssid, password);
    Serial.println("Connecting to WiFi...");
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }
    Serial.println("\nConnected to WiFi");

    pinMode(ledPin, OUTPUT);

    // Connect to WebSocket
    client.onMessage([](WebsocketsMessage message) {
        String data = message.data();
        Serial.println("Received: " + data);

        // Control LED based on received message
        if (data == "ON") {
            digitalWrite(ledPin, HIGH);
        } else if (data == "OFF") {
            digitalWrite(ledPin, LOW);
        }
    });

    // Handle WebSocket disconnection
    client.onEvent([](WebsocketsEvent event, String data) {
        if (event == WebsocketsEvent::ConnectionClosed) {
            Serial.println("WebSocket connection closed, reconnecting...");
            reconnectWebSocket();
        }
    });

    reconnectWebSocket(); // Connect WebSocket
}

void reconnectWebSocket() {
    while (!client.connect(websocketServer)) {
        Serial.println("Reconnecting to WebSocket...");
        delay(1000);
    }
    Serial.println("Connected to WebSocket");
}

void loop() {
    if (client.available()) {
        client.poll();
    }

    // Send LED status periodically
    static unsigned long lastSendTime = 0;
    unsigned long currentMillis = millis();
    if (currentMillis - lastSendTime >= 5000) { // Every 5 seconds
        lastSendTime = currentMillis;

        String ledStatus = digitalRead(ledPin) == HIGH ? "ON" : "OFF";
        client.send(ledStatus);
        Serial.println("Sent status: " + ledStatus);
    }
}
