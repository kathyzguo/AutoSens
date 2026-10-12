#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "variables.h"

Adafruit_SSD1306 display(128, 64, &Wire, -1);

void displayStart() {
    Wire.begin(SDAPIN, SCLPIN);
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) for (;;);
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println("Started!");
    display.display();
}

void displayText(String text) {
    display.clearDisplay();
    display.println(text);
    display.display();
}

void setDisplaySettings(int x = 0, int y = 0, int size = 2, uint16_t color = SSD1306_WHITE) {
    display.setTextColor(color);
    display.setTextSize(size);
    display.setCursor(x, y);
}