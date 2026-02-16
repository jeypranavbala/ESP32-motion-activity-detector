# Arduino Wearable Health Monitoring & Fall Detection  
(MAX30102 + MPU6050 + NEO-6M GPS + HC-05 Bluetooth)

Multi-sensor Arduino-based health monitoring system integrating physiological sensing, motion analysis, GPS tracking, and Bluetooth connectivity.

## Features

- Heart rate / SpO₂ raw sensing (MAX30102)
- 3-axis acceleration monitoring (MPU6050)
- Fall detection using acceleration magnitude
- GPS location tracking (NEO-6M)
- Bluetooth HC-05 connectivity detection
- Serial telemetry output
- Multi-sensor fusion on Arduino

## Microcontroller

Arduino UNO / Nano (ATmega328P)

## Hardware Components

- Arduino UNO / Nano  
- MAX30102 Pulse Oximeter Sensor  
- MPU6050 Accelerometer/Gyroscope  
- u-blox NEO-6M GPS Module  
- HC-05 Bluetooth Module  

## Pin Connections (Arduino)

### I²C Sensors

| Device | Arduino Pin |
|--------|------------|
| MAX30102 SDA | A4 |
| MAX30102 SCL | A5 |
| MPU6050 SDA | A4 |
| MPU6050 SCL | A5 |

### GPS (NEO-6M)

| NEO-6M | Arduino |
|--------|--------|
| TX | D10 |
| RX | D11 |
| VCC | 5V |
| GND | GND |

### Bluetooth HC-05

| HC-05 | Arduino |
|------|--------|
| TX | D8 |
| RX | D9 |
| VCC | 5V |
| GND | GND |

## Fall Detection Logic

Acceleration magnitude is computed from MPU6050:

sqrt(ax² + ay² + az²) > 2.5 g


If threshold is exceeded → fall detected.

## Output

Serial Monitor provides:

- IR & Red values (MAX30102)
- Acceleration in g (MPU6050)
- Fall detection status
- GPS coordinates
- Bluetooth connection state

## GPS Module

u-blox NEO-6M GPS receiver with ceramic patch antenna.  
The antenna must face upward toward open sky for reliable satellite lock.

## Applications

- Wearable health monitoring
- Elderly fall detection
- Remote patient tracking
- Athlete motion monitoring
- IoT health devices




sqrt(ax² + ay² + az²) > 2.5 g
