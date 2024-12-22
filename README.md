# Home Power Status Check

This project monitors the power status of a home using a NodeMCU and displays the status on a web dashboard.

## Project Structure

- `app.js`: The main server file using Express.js.
- `nodeMCU_code.c`: The code for the NodeMCU to send power status updates.
- `package.json`: Contains project metadata and dependencies.
- `public/index.html`: The web dashboard to display the power status.

## Setup

1. Clone the repository:
    ```sh
    git clone <repository-url>
    cd <repository-directory>
    ```

2. Install the dependencies:
    ```sh
    npm install
    ```

3. Start the server:
    ```sh
    npm start
    ```

4. Open your browser and navigate to `http://localhost:3005` to view the dashboard.

## NodeMCU Setup

1. Flash the  to your NodeMCU.
2. Connect the NodeMCU to your WiFi network by updating the `ssid` and `password` in the code.
3. The NodeMCU will send power status updates to the server every minute.

## API Endpoints

- `GET /`: Serves the web dashboard.
- `POST /update-status`: Updates the power status.
- `GET /get-status`: Retrieves the current power status.

## Cron Job

A cron job is scheduled to delete the `power_status.json` file at the start of every month to reset the data.

## License

This project is licensed under the ISC License.

## Author

Indal Singh