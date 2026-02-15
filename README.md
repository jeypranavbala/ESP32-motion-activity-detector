# ESP32 Activity Monitoring System (MPU6050 + OLED)

This project implements a real-time activity monitoring system using an ESP32, MPU6050 accelerometer, and SSD1306 OLED display.  
The system detects user activity based on motion intensity using variance-based signal analysis and displays the current activity state.

The implementation uses a sliding window algorithm with a circular buffer to classify motion as Sitting, Walking, or Running.

This project was developed for embedded systems, sensor interfacing, and real-time signal processing practice.

---

## Features

- Real-time motion detection using MPU6050 accelerometer
- Variance-based activity classification
- Sliding window signal processing
- Circular buffer implementation
- OLED display visualization
- Touch sensor based UI state switching
- Animation and activity monitoring modes
- Noise-resistant motion detection

---

## Hardware Used

- ESP32 Development Board
- MPU6050 Accelerometer Sensor
- SSD1306 OLED Display (128×64)
- Touch Sensor
- I2C Communication Interface

---

## System Overview

The system continuously reads acceleration data from the MPU6050 sensor and computes motion intensity using statistical variance over a sliding window of samples.

### System Workflow

1. MPU6050 provides acceleration readings.
2. ESP32 computes total acceleration magnitude.
3. Recent samples are stored in a circular buffer.
4. Motion variance is calculated over the sliding window.
5. Activity is classified based on motion intensity.
6. OLED displays detected activity.

---

## Motion Detection Method

Instead of simple threshold-based classification, the system uses variance-based signal analysis.

### Algorithm

- Collect N acceleration samples (sliding window).
- Compute mean acceleration.
- Compute variance of samples.
- Classify activity based on motion intensity.

### Variance Formula



This approach improves stability and reduces false detection caused by sensor noise.

---

## Activity Classification

| Motion Variance | Activity |
|---|---|
Low variance | Sitting |
Medium variance | Walking |
High variance | Running |

---

## Software Architecture

- ESP32 firmware (Arduino framework)
- I2C communication with MPU6050 and OLED
- Circular buffer implementation
- Sliding window variance calculation
- State machine for UI control

---

## Libraries Used

- Adafruit MPU6050
- Adafruit SSD1306
- Adafruit Sensor
- Wire (I2C)

---

## Sampling Behavior

- Sensor sampled every 200 ms
- Sliding window size: 20 samples
- First stable detection after buffer initialization (~4 seconds)

---

## Learning Outcomes

This project demonstrates:

- Embedded sensor interfacing
- I2C communication
- Real-time data processing
- Signal processing in embedded systems
- Circular buffer design
- Statistical motion analysis
- Embedded display control

---

## Future Improvements

- Low-pass filtering for additional noise reduction
- Step detection algorithm
- Interrupt-based sampling
- Sensor calibration
- Power optimization

---

## Author

Jey Pranav Bala Baluchamy Balamurugan  
Embedded Systems Engineer
