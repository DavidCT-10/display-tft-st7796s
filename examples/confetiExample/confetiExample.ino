#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Display_TFT_ST7796S.h"

#define TFT_RST 8
#define TFT_DC 9
#define TFT_CS 10
#define TFT_MOSI 11
#define TFT_MISO 12
#define TFT_CLK 13

// Change pins as desired
Display_ST7796S tft = Display_ST7796S(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);

#define ROTATION 3
#define TIRQ_PIN 2

word RgbToTft(byte R, byte G, byte B) {
  // TFT needs an 16 bit colour value 5 bit red, 6 bit green, 5 bit blue - RRRRRGGGGGGBBBBB
  return (((R & 0xF8) << 8) | ((G & 0xF4) << 3) | (B >> 3));
}

class Rectangle {
public:
  int x;
  int y;
  int oldX;
  int oldY;
  int vx;
  int vy;
  int width;
  int height;
  int colour;

  Rectangle() {
    width = random(5, 10);
    height = random(5, 10);
    x = random(0, tft.width() - width);
    y = random(0, tft.height() - height);
    oldX = x;
    oldY = y;
    vx = random(1, 5);
    vy = random(1, 5);
    byte R = (byte)random(64, 255);
    byte G = (byte)random(64, 255);
    byte B = (byte)random(64, 255);
    colour = (int)RgbToTft(R, G, B);
  }

  void move() {
    x += vx;
    y += vy;
    if ((x <= 0) || (x >= tft.width() - width)) {
      vx = -vx;
    }
    if ((y <= 0) || (y >= tft.height() - height)) {
      vy = -vy;
    }
  }

  void render() {
    tft.fillRect(oldX, oldY, width, height, ST7796S_BLACK);
    tft.fillRect(x, y, width, height, colour);
    oldX = x;
    oldY = y;
  }
};

int numRectangles = 40;
Rectangle rects[40];

void setup() {
  pinMode(TFT_CS, OUTPUT);
  digitalWrite(TFT_CS, HIGH);
  delay(10);
  tft.begin();
  tft.setRotation(ROTATION);
  tft.fillScreen(ST7796S_BLACK);
  delay(10);

  // create rectangles
  for (int rectCount = 0; rectCount < numRectangles; rectCount++) {
    rects[rectCount] = Rectangle();
  }
}




unsigned long lastFrame = millis();
int frameDisplayTimer = 20;

void loop(void) {

  frameDisplayTimer--;
  if (frameDisplayTimer == 0) {
    frameDisplayTimer = 20;
    // print frame time
    tft.fillRect(0, 0, 30, 15, ST7796S_BLACK);
    tft.setCursor(0, 0);
    tft.setTextSize(2);
    tft.setTextColor(ST7796S_WHITE);
    tft.print(millis() - lastFrame);
  }


  while ((millis() - lastFrame) < 20)
    ;
  lastFrame = millis();

  for (int rectCount = 0; rectCount < numRectangles; rectCount++) {
    rects[rectCount].move();
    rects[rectCount].render();
  }
}