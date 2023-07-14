#include "Numbers.h"
#include <ESP32Time.h>
#include <FastLED.h>
#include <LEDMatrix.h>

#define BUTTON_PIN 21
#define LED_PIN 13
#define BRIGHTNESS 100

#define WIDTH 16
#define HEIGHT 5
#define NUM_LEDS (WIDTH * HEIGHT)
#define COLON_COLUMN 8

cLEDMatrix<WIDTH, HEIGHT, HORIZONTAL_ZIGZAG_MATRIX> leds;

ESP32Time rtc;

void setup() {
  Serial.begin(115200);
  delay(500);

  pinMode(BUTTON_PIN, INPUT_PULLUP);

  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds[0], NUM_LEDS);

  // rtc.setTime(s, min, hr, day, month, year)
  rtc.setTime(0, 34, 13, 14, 7, 2023);
}

void loop() {
  FastLED.clear();

  // Test read button state
  int buttonRead = digitalRead(BUTTON_PIN); // LOW when button held
  if (buttonRead == LOW) {
    Serial.println("ON");
  } else {
    Serial.println("OFF");
  }

  int hour = rtc.getHour();
  int minute = rtc.getMinute();
  showTime(hour / 10, hour % 10, minute / 10, minute % 10);

  Serial.println(rtc.getTime("%H:%M:%S"));

  // flipHorizontal();
  flipVertical();

  FastLED.setBrightness(BRIGHTNESS);
  FastLED.show();

  delay(1000);
}

void showTime(int d1, int d2, int d3, int d4) {
  if (d1 != 0) {
    showDigit(digits[d1], 0);
  }
  showDigit(digits[d2], 4);
  showColon();
  showDigit(digits[d3], 9);
  showDigit(digits[d4], 13);
}

void showColon() {
  static bool colonOn = true;
  colonOn = !colonOn;
  if (colonOn) {
    leds(COLON_COLUMN, 1) = CHSV(0, 0, BRIGHTNESS); // White
    leds(COLON_COLUMN, 3) = CHSV(0, 0, BRIGHTNESS); // White
  }
}

void showDigit(Digit digit, int startColumn) {
  for (int x = 0; x < DIGIT_WIDTH; x++) {
    for (int y = 0; y < DIGIT_HEIGHT; y++) {
      if (digit.pixels[y][x]) {
        int hue = map(startColumn + x, 0, WIDTH, 0, 255);
        CHSV color = CHSV(hue, 255, BRIGHTNESS);
        leds(startColumn + x, y) = color;
      } else {
        leds(startColumn + x, y) = CRGB::Black;
      }
    }
  }
}
