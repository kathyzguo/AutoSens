#include <Arduino.h>
#include <WiFi.h>
#include "time.h"
#include "esp_sntp.h"

// 1. eduroam Network Credentials
const char* ssid = "eduroam";
#define EAP_IDENTITY "kzg7@cornell.edu" 
#define EAP_USERNAME "kzg7@cornell.edu" 
#define EAP_PASSWORD "cDmag3ni^2iplkpewWH9rv0{DXE<%>}"             

// 2. Time Server Settings
const char* ntpServer1 = "pool.ntp.org";
const char* ntpServer2 = "time.nist.gov";
const long gmtOffset_sec = -18000;     // Eastern Time Zone Example (-5 hours)
const int daylightOffset_sec = 3600;   // 1 hour for Daylight Savings

void printLocalTime() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("No time available (yet)");
    return;
  }
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
}

void timeavailable(struct timeval *t) {
  Serial.println("\n🎉 SUCCESS! Received time adjustment from NTP!");
}

void setup() {
  Serial.begin(115200);
  delay(1500); 

  Serial.println("\n=== SYSTEM START ===");

  // Initialize time settings
  sntp_set_time_sync_notification_cb(timeavailable);
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer1, ntpServer2);

  // Initialize Wi-Fi Station Mode
  WiFi.disconnect(true);
  WiFi.mode(WIFI_STA);

  Serial.println("Attempting streamlined eduroam connection...");
  
  // --- THE EASIER METHOD ---
  // Parameters: SSID, Auth Mode, Identity, Username, Password
  WiFi.begin(ssid, WPA2_AUTH_PEAP, EAP_IDENTITY, EAP_USERNAME, EAP_PASSWORD);

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\n✅ Wi-Fi Connection Established!");
  Serial.print("Assigned IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  delay(5000);
  printLocalTime();
}