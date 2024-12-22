#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "Indal Singh";
const char* password = "987654321";
const char* apiEndpoint = "http://test.raagdhun.in/update-status";

WiFiClient wifiClient; // Create a WiFi client

// Define the GPIO pin for the LED
const int ledPin = D0;

void setup() {
    Serial.begin(115200);
    WiFi.begin(ssid, password);

    pinMode(ledPin, OUTPUT); // Set D0 as an output pin

    Serial.println("before connect");
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }

    Serial.println("Connected to WiFi");
}

void loop() {
    // Blink the D0 light
    digitalWrite(ledPin, HIGH); // Turn the LED on
    delay(500);                // Wait for 500 ms
    digitalWrite(ledPin, LOW);  // Turn the LED off
    delay(500);                // Wait for 500 ms

    if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;

        // Use the new begin syntax
        http.begin(wifiClient, apiEndpoint);
        http.addHeader("Content-Type", "application/json");

        String payload = "{\"status\": \"ON\"}";
        int httpResponseCode = http.POST(payload);

        if (httpResponseCode > 0) {
            String response = http.getString();
            Serial.println("Response: " + response);
        } else {
            Serial.println("Error: " + String(httpResponseCode));
        }

        http.end();
    } else {
        Serial.println("WiFi Disconnected. Reconnecting...");
        WiFi.begin(ssid, password);
    }

    delay(60000 - 1000);  // Subtract the blinking delay
}
