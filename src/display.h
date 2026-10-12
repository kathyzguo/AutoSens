#include <Arduino.h>
#include <Adafruit_SSD1306.h>
#pragma once

void displayStart();
void displayText(String text);
void setDisplaySettings(int x = 0, int y = 0, int size = 2, uint16_t color = SSD1306_WHITE);