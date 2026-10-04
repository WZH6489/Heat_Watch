# HeatWatch

Real-time indoor heat safety monitor for older adults. An Arduino with a DHT temperature/humidity sensor streams readings over USB, and a browser dashboard turns them into heat-risk levels, alerts, and caregiver check-in reminders.

## Features

- Live readings over USB using the Web Serial API (no server or install needed)
- Four heat levels (Normal, Caution, Warning, Danger) based on temperature and heat index, with plain-language actions
- Live 2-minute chart plus 30-minute, 3-hour, and 24-hour history with shaded risk zones
- 5-minute, 1-hour, and 24-hour averages, low/high, and time spent above thresholds
- Alerts for rapid temperature rise, rooms that don't cool overnight, and sensor dropouts
- Caregiver check-in reminders that get more frequent as risk rises
- Optional alarm sound and browser notifications, CSV export
- Built-in demo mode with a simulated heat wave

## Hardware

- Arduino Uno (or compatible, e.g. Elegoo Uno R3)
- DHT11 sensor on digital pin 2 (DHT22 or SHT31 recommended for better accuracy)

## Setup

1. Install the Elegoo `DHT_nonblocking` library in the Arduino IDE.
2. Open `arduino/heatwatch_dht/heatwatch_dht.ino` and upload it to the board.
3. Close the Arduino IDE Serial Monitor (only one program can use the port).
4. Open the dashboard in **Chrome or Edge** (desktop): either the hosted GitHub Pages link or `index.html` directly.
5. Choose **9600 baud** and click **Connect Arduino**. On Elegoo boards the port is listed as `USB2.0-Serial`.

The dashboard also accepts the original Elegoo sample output format (`T = 23.0 deg. C, H = 45.0%`).

## Heat thresholds

Defaults follow BC public health guidance for heat-vulnerable people: keep indoor temperatures below 26 °C, and treat indoor temperatures above 31 °C as dangerous. All thresholds can be changed in the dashboard settings.

## Disclaimer

HeatWatch supports, and does not replace, in-person checks. The DHT11 is accurate to about ±2 °C.
