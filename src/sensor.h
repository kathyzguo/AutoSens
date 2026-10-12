#pragma once

struct sensorData {
    float humidity;
    float temperature;
    float dewpoint;
    float heatIndex;
    int light;
};

void sensorStart();
sensorData getSensorInfo();
String sensorDataToString(const sensorData& d);