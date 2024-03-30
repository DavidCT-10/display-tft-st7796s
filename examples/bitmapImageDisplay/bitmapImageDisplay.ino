
#include "SPI.h"
#include "Display_TFT_ST7796S.h"
#include "dragon.h"

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
  tft.begin();
  tft.setRotation(1);
}

void loop(void) {

  tft.fillScreen(ST7796S_BLACK);
  for (uint16_t x = 0; x <= 330; x += 110){
    tft.drawRGBBitmap(x,0,dragonBitmap,DRAGON_WIDTH, DRAGON_HEIGHT);
    tft.drawRGBBitmap(x,70,dragonBitmap,DRAGON_WIDTH, DRAGON_HEIGHT);
    tft.drawRGBBitmap(x,140,dragonBitmap,DRAGON_WIDTH, DRAGON_HEIGHT);
    tft.drawRGBBitmap(x,210,dragonBitmap,DRAGON_WIDTH, DRAGON_HEIGHT);
  }
  Serial.println("Tada");
  delay(5000);
}

