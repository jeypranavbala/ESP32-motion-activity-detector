# ESP32-motion-activity-detector
ESP32-based activity monitoring system using MPU6050 accelerometer and OLED display with real-time motion detection.
# ESP32 Activity Monitoring System (MPU6050 + OLED)

This project implements a real-time activity monitoring system using an ESP32, MPU6050 accelerometer sensor, and SSD1306 OLED display.

The system detects user activity (Sitting, Jogging, Running) based on acceleration data and displays the current status on the OLED screen. A touch sensor is used to switch between animation and activity monitoring modes.

This project was developed for embedded systems and sensor interfacing practice.

---

## Features

- Real-time activity detection using MPU6050 accelerometer
- Motion classification (Sitting / Jogging / Running)
- OLED display visualization using SSD1306
- Touch sensor-based UI state switching
- Simple animation display mode
- Activity timeout and automatic screen switching
- I2C communication with sensors and display

---

## Hardware Used

- ESP32 Development Board
- MPU6050 Accelerometer Sensor
- SSD1306 OLED Display (128×64)
- Touch Sensor
- I2C Communication Interface

---

## System Overview

The system reads acceleration data from the MPU6050 sensor and computes total acceleration magnitude. Based on threshold values, the firmware classifies the user's activity and displays the result.

### System Workflow

1. MPU6050 provides acceleration data.
2. ESP32 calculates total acceleration magnitude.
3. Activity is classified using threshold comparison.
4. OLED displays animation or activity status.
5. Touch sensor toggles system state.

---

## Activity Classification Logic

| Acceleration Range | Activity |
|---|---|
| ≤ 11 m/s² | Sitting |
| 11 – 13 m/s² | Jogging |
| > 13 m/s² | Running |

---

## Software Components

- ESP32 firmware (Arduino framework)
- MPU6050 sensor driver
- SSD1306 display driver
- I2C communication interface
- State machine for UI control

---

## Libraries Used

- Adafruit MPU6050
- Adafruit SSD1306
- Adafruit Sensor
- Wire (I2C)

---

## How to Run

1. Open project in Arduino IDE.
2. Install required libraries.
3. Select ESP32 board.
4. Connect MPU6050 and OLED via I2C.
5. Upload firmware to ESP32.

---

## Learning Outcomes

- Embedded sensor interfacing
- I2C communication
- Real-time data processing
- Activity detection logic
- Embedded display control
- State machine design

---

## Author

Jey Pranav Bala Baluchamy Balamurugan  
Embedded Systems Engineer
