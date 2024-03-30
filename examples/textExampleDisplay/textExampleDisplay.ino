#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Display_TFT_ST7796S.h"

/*
Connections Example:
GND     ----------->  GND
VIN     ----------->  5v - 3.3V
SCL     --> SCLK -->  PIN 13
SDA     --> MOSI -->  PIN 11
RST     ----------->  PIN 8
DC      ----------->  PIN 9
CS      ----------->  PIN 10
BL      ----------->  POtentiometer (5v-0V) = Display BrightLight
SDA-0   ----------->  PIN ???
*/

#define TFT_RST 8
#define TFT_DC 9
#define TFT_CS 10
#define TFT_MOSI 11
#define TFT_MISO 12
#define TFT_CLK 13

// Change pins as desired
Display_ST7796S tft = Display_ST7796S(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);

void setup() {
  Serial.begin(9600);
  Serial.println("Display TFT ST7796S Test!"); 
 
  tft.begin();
  Serial.println(F("Done!"));

}


void loop(void) {
  for(uint8_t rotation=0; rotation<4; rotation++) {
    Serial.println("Rotation: " + String(rotation) + "/3");
    tft.setRotation(rotation);
    testText();
    delay(1000);
  }
}

unsigned long testText() {
  tft.fillScreen(ST7796S_BLACK);
  unsigned long start = micros();
  tft.setCursor(0, 0);
  tft.setTextColor(ST7796S_WHITE);  tft.setTextSize(1);
  tft.println("Hello World!");
  tft.setTextColor(ST7796S_YELLOW); tft.setTextSize(2);
  tft.println(1234.56);
  tft.setTextColor(ST7796S_RED);    tft.setTextSize(3);
  tft.println(0xDEADBEEF, HEX);
  tft.println();
  tft.setTextColor(ST7796S_GREEN);
  tft.setTextSize(5);
  tft.println("Groop");
  tft.setTextSize(2);
  tft.println("I implore thee,");
  tft.setTextSize(1);
  tft.println("my foonting turlingdromes.");
  tft.println("And hooptiously drangle me");
  tft.println("with crinkly bindlewurdles,");
  tft.println("Or I will rend thee");
  tft.println("in the gobberwarts");
  tft.println("with my blurglecruncheon,");
  tft.println("see if I don't!");
  return micros() - start;
}
