🌱AquaGrow – Smart Soil Moisture Monitoring & Motor Control
AquaGrow is a simple yet effective IoT-based soil moisture monitoring system using an ESP8266 (NodeMCU). It features a real-time web interface to display soil moisture levels and automatically control a motor (pump) based on soil dryness.

🚀 Features
📡 WiFi Access Point (AP Mode) – No external WiFi needed
🌡️ Real-time Soil Moisture Monitoring (0-100%)
🔄 Auto Motor Control – Turns ON when moisture is low
📊 Interactive Web Dashboard with a circular progress bar
💡 Onboard LED Indicator for motor status

🛠️ Components Used
ESP8266 NodeMCU – Microcontroller
Soil Moisture Sensor (Analog)
Water Pump / Motor (Optional, Controlled via Relay)
Jumper Wires & Breadboard

📜 How It Works
The ESP8266 hosts a web server that displays real-time soil moisture.
The soil moisture sensor reads analog values and converts them to a percentage (0-100%).
If moisture is below 40%, the motor (pump) is turned ON, and if it exceeds 40%, the motor is turned OFF.
The progress bar updates dynamically on the web interface.

🔧 Installation & Setup
Upload the provided code to your ESP8266 using Arduino IDE.
Connect the soil moisture sensor to A0 pin of ESP8266.
Power the ESP8266 and connect to its WiFi (NodeMCU_AP / 12345678).
Open a browser and navigate to 192.168.4.1 to access the dashboard.

🔗 Future Improvements
🔌 Integration with Blynk / MQTT for remote monitoring
📱 Mobile App Interface
🌦️ Weather-based Irrigation Scheduling
