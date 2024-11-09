# Wi-Fi-Tracker - Wi-Fi Signal Strength Analyzer + Intruder Signal Source Locator

![Meme](https://i.imgflip.com/7jjdgk.jpg)
*"When your ESP8266 detects an intruder and they're closer than you think!"*

## Overview
This ESP8266-based project detects nearby devices and measures their signal strength (RSSI) to estimate proximity. It logs any unauthorized devices attempting to access the network and provides information on their relative distance based on signal strength.

---

## Disclaimer
This project is intended for educational and ethical use only. Unauthorized network monitoring and device detection may be restricted in some regions. Use responsibly and with permission. The authors are not responsible for any misuse or legal consequences.

---

## Features
- **Signal Strength Analysis**: Measures signal strength (RSSI) of devices detected on the network, providing proximity estimation.
- **Intruder Detection**: Logs any unauthorized device connections and alerts based on proximity.
- **Web Interface**: View detected intruders and signal strength data in real time.

## Installation

### Requirements
- **ESP8266** (e.g., NodeMCU)
- **Arduino IDE** with ESP8266 library
- **Wi-Fi credentials** (SSID and password)

### Setup
1. **Install ESP8266 Board in Arduino IDE**:
   - Go to **File > Preferences**.
   - Add `http://arduino.esp8266.com/stable/package_esp8266com_index.json` under **Additional Board Manager URLs**.
   - Go to **Tools > Board > Board Manager**, search for **ESP8266**, and install.

2. **Upload the Code**:
   - Replace `primarySSID` and `primaryPassword` with your network details.
   - Add known device MAC addresses in `authorizedDevices[]` to identify trusted devices.
   - Select the **ESP8266 board** and **COM port** in **Tools**, then upload the code.

3. **Access the Web Interface**:
   - Connect a device to the ESP8266’s network.
   - Enter the ESP8266’s IP address (usually `192.168.4.1`) in a browser to access the web interface.

---

## How to Use
1. **Signal Strength Analysis**:
   - The ESP8266 detects nearby devices and measures their RSSI, estimating proximity.
   - Devices with higher RSSI values are closer to the network.

2. **Intruder Detection**:
   - Unauthorized devices are identified based on MAC addresses.
   - If a device is detected with an RSSI higher than the set threshold, it indicates close proximity to the network.

3. **Web Interface**:
   - Use the web interface to view the number of detected intruders and adjust the RSSI threshold for proximity alerts.

## Advantages
- Helps locate nearby unauthorized devices based on signal strength.
- Provides easy monitoring of detected devices and their relative distances.
- Lightweight and accessible through a web interface.

## Disadvantages
- Limited to detecting unauthorized devices based on MAC address filtering.
- RSSI-based proximity estimation is approximate and may vary based on environmental factors.
- May not prevent intrusions but provides visibility into nearby device activity.

## License
This project is open-source and available under the MIT License.
