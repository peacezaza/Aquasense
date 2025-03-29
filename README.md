Aquasense

Aquasense is an ESP32-based project utilizing RTOS to monitor and control water quality parameters in a fish farm. The system ensures stable levels of oxygen, pH, and turbidity to optimize fish health and growth.

Features

Real-time Monitoring: Continuously measures oxygen levels, pH, and turbidity.

RTOS-based Control: Uses FreeRTOS to efficiently manage sensor readings, data processing, and control logic.

Automated Adjustments: Maintains optimal water quality by adjusting aerators, chemical dosing, or filtration.

Data Logging & Alerts: Logs data and provides alerts if values go out of range.

Wireless Connectivity: Supports Wi-Fi for remote monitoring and control.

Hardware Requirements

ESP32 (supports Wi-Fi & RTOS)

Dissolved Oxygen Sensor

pH Sensor

Turbidity Sensor

Relay Modules (for controlling aerators, pumps, or chemical dosing systems)

Power Supply (suitable for ESP32 and peripherals)

Software Stack

FreeRTOS (for multitasking)

Arduino Framework (or ESP-IDF)

MQTT / HTTP (for remote monitoring)

SPI / I2C Communication (for sensor interfacing)

Installation & Setup

Flash the ESP32 with the firmware using PlatformIO or Arduino IDE.

Connect sensors and actuators as per the wiring diagram.

Configure Wi-Fi and MQTT credentials in the firmware.

Deploy the system in your fish farm and monitor readings in real time.