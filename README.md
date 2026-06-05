# 🏭 Industrial Air Quality Monitoring System

An IoT-based Industrial Air Quality Monitoring System developed using ESP32, DHT11, MQ135, MQ7, MQ5, OLED Display, and Firebase Realtime Database.

This system continuously monitors industrial environmental conditions such as temperature, humidity, air quality, carbon monoxide concentration, and combustible gases. The collected data is displayed locally on an OLED screen and uploaded to Firebase Cloud for real-time remote monitoring and analysis.

---

## 🚀 Features

- Real-Time Air Quality Monitoring
- Temperature Monitoring
- Humidity Monitoring
- Carbon Monoxide Detection
- LPG and Smoke Detection
- OLED Display Interface
- Firebase Cloud Integration
- Wi-Fi Connectivity
- Warning and Danger Alert System
- Industrial Safety Monitoring
- Remote Data Access

---

## 🎯 Project Objectives

- Monitor harmful gases in industrial environments.
- Detect abnormal environmental conditions.
- Provide early warning alerts for workers.
- Store and access environmental data remotely.
- Improve workplace safety through continuous monitoring.

---

## 🛠 Hardware Components

- ESP32 Development Board
- DHT11 Temperature & Humidity Sensor
- MQ135 Air Quality Sensor
- MQ7 Carbon Monoxide Sensor
- MQ5 LPG/Smoke Sensor
- SSD1306 OLED Display
- Buzzer
- LEDs
- Breadboard
- Jumper Wires

---

## 🔌 Pin Configuration

| Component | ESP32 Pin |
|------------|------------|
| DHT11 | GPIO 15 |
| MQ135 | GPIO 34 |
| MQ7 | GPIO 35 |
| MQ5 | GPIO 32 |
| OLED MOSI | GPIO 23 |
| OLED CLK | GPIO 18 |
| OLED DC | GPIO 2 |
| OLED CS | GPIO 5 |
| OLED RESET | GPIO 4 |
| LED1 | GPIO 19 |
| LED2 | GPIO 21 |
| Buzzer | GPIO 22 |

---

## ⚙ Working Principle

1. ESP32 collects data from DHT11 and MQ sensors.
2. Sensor values are analyzed to determine air quality status.
3. Data is displayed on the OLED screen.
4. Real-time readings are uploaded to Firebase.
5. Alert mechanisms are activated when thresholds are exceeded.
6. Users can monitor environmental conditions remotely through Firebase.

---

## 📊 Monitoring Parameters

- Temperature (°C)
- Humidity (%)
- Air Quality Index (MQ135)
- Carbon Monoxide Level (MQ7)
- LPG/Smoke Level (MQ5)

---

## 🚨 Alert Levels

### SAFE
Normal environmental conditions.

### WARNING
Moderately elevated gas concentration or temperature.

### DANGER
Critical gas concentration or unsafe environmental conditions.

Actions:
- Red LED Activated
- Continuous Buzzer Alert

---

## ☁ Firebase Database Structure

```json
{
  "AirQuality": {
    "Temperature": 28.5,
    "Humidity": 65,
    "MQ135": 980,
    "MQ7": 850,
    "MQ5": 900,
    "Status": "SAFE"
  }
}
```

---

## 📚 Software Requirements

- Arduino IDE
- ESP32 Board Package
- Firebase ESP Client Library
- Adafruit SSD1306 Library
- Adafruit GFX Library
- DHT Sensor Library

---

## 🏭 Industrial Applications

- Manufacturing Plants
- Chemical Industries
- Oil and Gas Facilities
- Warehouses
- Power Plants
- Mining Operations
- Smart Factories
- Environmental Monitoring Stations

---

## Future Enhancements

- Mobile App Integration
- SMS/Email Alert System
- AI-Based Air Quality Prediction
- Data Analytics Dashboard
- GPS-Based Monitoring
- Multi-Node Industrial Network

---

## Author

Harishankar Prajapati

M.Tech (Internet of Things)

---

## License

This project is licensed under the MIT License.
