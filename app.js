const express = require('express');
const fs = require('fs');
const path = require('path');
const cron = require('node-cron');

const app = express();
app.use(express.json());

let powerStatus = [];

app.use(express.static(path.join(__dirname, "public")));

app.get('/', (req, res) => {
    res.sendFile(path.join(__dirname, "public", "index.html"));
});

app.post('/update-status', (req, res) => {
    const { status } = req.body;
    powerStatus.push({ status, timestamp: new Date() });
    fs.writeFileSync('power_status.json', JSON.stringify(powerStatus));
    res.status(200).send('Status updated.');
});

app.get('/get-status', (req, res) => {
    try {
        const data = fs.readFileSync('power_status.json', 'utf8');
        res.json(JSON.parse(data));
    } catch (error) {
        res.status(500).send('Error reading status file');
    }
});

// Schedule a task to delete power_status.json at the start of every month
cron.schedule('0 0 1 * *', () => {
    try {
        if (fs.existsSync('power_status.json')) {
            fs.unlinkSync('power_status.json'); // Delete the file
            console.log('power_status.json deleted for a new month');
        }
    } catch (err) {
        console.error('Error deleting power_status.json:', err);
    }
}, {
    scheduled: true,
    timezone: "Asia/Kolkata" // Set to IST (India Standard Time)
});

const port = 3005;
app.listen(port, () => console.log(`Server running on port ${port}`));
