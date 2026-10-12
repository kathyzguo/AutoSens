#include <Arduino.h>
#include <DHT.h>
#include "sensor.h"
#include "variables.h"

static DHT dht(DHTPIN, DHTTYPE);

void sensorStart() {
    dht.begin();
    analogReadResolution(12);
    analogSetPinAttenuation(LDRPIN, ADC_11db);
}

static float dewPoint(float t, float rh) {
    float a = 17.62, b = 243.12;
    float g = log(rh / 100.0) + (a * t) / (b + t);
    return (b * g) / (a - g);
}

static int avgOutLight() {
    long sum = 0;
    for (int i = 0; i < 16; i++) {
        sum += analogRead(LDRPIN);
    }
    return sum / 16;
}

sensorData getSensorInfo() {
    sensorData data;
    data.humidity = dht.readHumidity();
    data.temperature = dht.readTemperature();
    data.heatIndex = dht.computeHeatIndex(data.temperature, data.humidity, false);
    data.dewpoint = dewPoint(data.temperature, data.humidity);
    data.light = map(avgOutLight(), 0, 4095, 0, 100);
    return data;
}

String sensorDataToString(const sensorData& d) {
    return "Temp: " + String(d.temperature, 0) + "C\nHum: " + 
        String(d.humidity, 0) + "%\nLight: " + String(d.light) + "%";
}