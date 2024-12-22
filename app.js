const express = require('express');
const http = require('http');
const WebSocket = require('ws');
const path = require('path');

const app = express();
const server = http.createServer(app);
const wss = new WebSocket.Server({ server });

app.use(express.static(path.join(__dirname, 'public')));

// Handle WebSocket connection
wss.on('connection', (ws) => {
    console.log('A client connected.');

    // Listen for messages from the client
    ws.on('message', (message) => {
        console.log('Received:', message);

        // Broadcast the message to all connected clients except the sender
        wss.clients.forEach((client) => {
            if (client !== ws && client.readyState === WebSocket.OPEN) {
                client.send(message);
            }
        });
    });

    // Send a command to the client periodically
    const interval = setInterval(() => {
        const command = Math.random() > 0.5 ? 'ON' : 'OFF';
        ws.send(command); // Send command to the client
    }, 10000); // Every 10 seconds

    // Handle client disconnection
    ws.on('close', () => {
        console.log('A client disconnected.');
        clearInterval(interval); // Stop sending commands when client disconnects
    });
});

// Serve the HTML UI
app.get('/get-status', (req, res) => {
    res.sendFile(path.join(__dirname, 'public', 'index.html'));
});

// Start the server
server.listen(3005, () => {
    console.log('WebSocket server running on http://localhost:3005');
});
