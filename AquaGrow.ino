#include <ESP8266WiFi.h>
#include <ESPAsyncWebServer.h>

#define LED_PIN 2  // Onboard LED (D4 on NodeMCU)
#define MOTOR 16  // Onboard LED (D0 on NodeMCU)
#define SOIL_SENSOR A0  // Soil moisture sensor pin

// AP Credentials
const char* ssid = "NodeMCU_AP";  
const char* password = "12345678";  

AsyncWebServer server(80);

// Variables for Soil Moisture and Motor Status
int moistureValue = 0;
bool motorStatus = false;  // false = OFF, true = ON

void setup() {
    Serial.begin(115200);
    pinMode(LED_PIN, OUTPUT);
    pinMode(MOTOR, OUTPUT);
    digitalWrite(LED_PIN, HIGH);  // LED OFF by default
    digitalWrite(MOTOR, HIGH);  // MOTOR OFF by default

    WiFi.softAP(ssid, password);
    IPAddress IP = WiFi.softAPIP();
    Serial.print("\U0001F310 AP IP Address: ");
    Serial.println(IP);

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        String html = "<!DOCTYPE html><html><head>";
        html += "<meta name='viewport' content='width=device-width, initial-scale=1'>";
        html += "<title>AquaGrow</title>";
        html += "<style>";
        html += "body { font-family: Arial, sans-serif; text-align: center; background-color: #181818; color: white; padding: 20px; display: flex; justify-content: center; align-items: center; height: 100vh; margin: 0; }";
        html += ".container { width: 90%; max-width: 400px; padding: 20px; background: #222; border-radius: 15px; }";
        html += "h1 { color: #ffcc00; }";
        html += "h2 { color: white; }";
        html += ".progress-circle { width: 100%; max-width: 180px; height: auto; margin: 20px auto; position: relative; }";
        html += ".progress-circle svg { transform: rotate(-90deg); width: 100%; height: auto; }";
        html += ".progress-circle circle { fill: none; stroke-width: 14; stroke-linecap: round; }";
        html += ".progress-circle .bg { stroke: #444; }";
        html += ".progress-circle .progress { stroke: #ffcc00; transition: stroke-dashoffset 0.5s ease; }";
        html += ".progress-text { position: absolute; top: 50%; left: 50%; transform: translate(-50%, -50%); font-size: 26px; font-weight: bold; color: white; }";
        html += "</style>";
        html += "<script>";
        html += "function updateProgress() { fetch('/moisture').then(response => response.text()).then(data => { let progress = document.querySelector('.progress'); progress.style.strokeDashoffset = 314 - (314 * data / 100); document.getElementById('progress-text').innerText = data + '%'; fetch('/motorStatus').then(response => response.text()).then(status => { document.getElementById('motor-status').innerText = status; }); }); setTimeout(updateProgress, 1000); } window.onload = updateProgress;";
        html += "</script>";
        html += "</head><body>";
        html += "<div class='container'>";
        html += "<h1>AquaGrow</h1>";
        html += "<div class='progress-circle'>";
        html += "<svg viewBox='0 0 180 180'><circle cx='90' cy='90' r='50' class='bg'/><circle cx='90' cy='90' r='50' class='progress' stroke-dasharray='314' stroke-dashoffset='314'/></svg>";
        html += "<div id='progress-text' class='progress-text'>0%</div></div>";
        html += "<h2>Motor Status: <span id='motor-status'>" + String(motorStatus ? "ON" : "OFF") + "</span></h2>";
        html += "</div></body></html>";
        request->send(200, "text/html", html);
    });

    server.on("/moisture", HTTP_GET, [](AsyncWebServerRequest *request) {
        moistureValue = analogRead(SOIL_SENSOR);
        int moisturePercent = map(moistureValue, 1023, 0, 0, 100);
        if (moisturePercent < 40) {
            digitalWrite(LED_PIN, LOW); // LED ON
            digitalWrite(MOTOR, LOW); // MOTOR ON
            motorStatus = true;
        } else {
            digitalWrite(LED_PIN, HIGH); // LED OFF
            digitalWrite(MOTOR, HIGH); // MOTOR OFF
            motorStatus = false;
        }
        request->send(200, "text/plain", String(moisturePercent));
    });

    server.on("/motorStatus", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(200, "text/plain", motorStatus ? "ON" : "OFF");
    });

    server.begin();
}

void loop() {
    delay(1000);
}
