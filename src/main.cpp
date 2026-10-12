#include <Arduino.h>
#include <WiFi.h>
#include "secrets.h"
#include "sensor.h"
#include "display.h"

void connect() {
    Serial.println("\n=== SYSTEM START ===");

    WiFi.disconnect(true);
    WiFi.mode(WIFI_STA);

    Serial.println("Attempting streamlined connection...");
    WiFi.begin(WIFI_SSID, WPA2_AUTH_PEAP, EAP_IDENTITY, EAP_USERNAME, EAP_PASSWORD);

    Serial.print("Connecting");
    while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    }

    Serial.println("\nWi-Fi Connection Established!");
}

void setup() {
    Serial.begin(115200);
    sensorStart();
    displayStart();
    setDisplaySettings(0, 0, 1);
}

void loop() {
    delay(5000);
    setDisplaySettings(0, 0);
    displayText(sensorDataToString(getSensorInfo()));
}