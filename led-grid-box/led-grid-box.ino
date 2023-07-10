#include <FastLED.h>
#include <LEDMatrix.h>
#include <LEDText.h>
#include "Numbers.h"

#define BUTTON_PIN 2
#define LED_PIN 3
#define BRIGHTNESS 100

#define WIDTH 16
#define HEIGHT 5
#define NUM_LEDS (WIDTH * HEIGHT)
#define COLON_Y 8

cLEDMatrix<WIDTH, HEIGHT, HORIZONTAL_ZIGZAG_MATRIX> leds;

void setup() {
  Serial.begin(115200);
  delay(500);

  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds[0], NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);

  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void loop() {
  int buttonRead = digitalRead(BUTTON_PIN); // LOW when button held
  if (buttonRead == LOW) {
    Serial.println("ON");
  } else {
    Serial.println("OFF");
  }

  //for (int x = 0; x < WIDTH; x++) {
  //  for (int y = 0; y < HEIGHT; y++) {
  //    int hue = map(y, 0, HEIGHT, 0, 255);
  //    leds(x, y) = CHSV(hue, 255, 255);
  //  }
  //}

  showNumber(0, 1);
  showNumber(1, 2);
  showNumber(2, 3);
  showNumber(3, 4);
  showColon(CRGB::Blue);
  FastLED.show();

  delay(100);
}

void showColon(CRGB color) {
  leds(COLON_Y, 0) = CRGB::Black;
  leds(COLON_Y, 1) = color;
  leds(COLON_Y, 2) = CRGB::Black;
  leds(COLON_Y, 3) = color;
  leds(COLON_Y, 4) = CRGB::Black;
}


void showNumber(int xPosition, int digit) {
  int xStart = xPosition * 4;
  xStart = xStart >= COLON_Y ? xStart + 1 : xStart;
  for (int x = 0; x < 3; x++) {
    for (int y = 0; y < 5; y++) {
      if (digits[digit].pixels[y][x]) {
        leds(xStart + x, y) = CRGB::White;
      } else {
        leds(xStart + x, y) = CRGB::Black;
      }
    }
  }
}
