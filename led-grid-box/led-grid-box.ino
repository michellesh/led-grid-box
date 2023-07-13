#include "Numbers.h"
#include <FastLED.h>
#include <LEDMatrix.h>
#include <LEDText.h>

#define BUTTON_PIN 2
#define LED_PIN 3
#define BRIGHTNESS 100

#define WIDTH 16
#define HEIGHT 5
#define NUM_LEDS (WIDTH * HEIGHT)
#define COLON_COLUMN 8

cLEDMatrix<WIDTH, HEIGHT, HORIZONTAL_ZIGZAG_MATRIX> leds;

void setup() {
  Serial.begin(115200);
  delay(500);

  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds[0], NUM_LEDS);

  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void loop() {
  unsigned long startMillis = millis();

  FastLED.clear();

  // Test read button state
  int buttonRead = digitalRead(BUTTON_PIN); // LOW when button held
  if (buttonRead == LOW) {
    // Serial.println("ON");
  } else {
    // Serial.println("OFF");
  }

  static long hour = 14;
  static long minute = 40;
  static long second = 0;

  second++;
  if (second > 59) {
    second = 0;
    minute++;
    if (minute > 59) {
      minute = 0;
      hour++;
      if (hour > 23) {
        hour = 0;
      }
    }
  }

  int h = convert24To12Hour(hour);
  showTime(h / 10, h % 10, minute / 10, minute % 10);

  // flipHorizontal();
  flipVertical();

  FastLED.setBrightness(BRIGHTNESS);
  FastLED.show();

  delay(1000 - getAvgLoopTime(startMillis));
}

int getAvgLoopTime(unsigned long startMillis) {
  static unsigned long sum = 0;
  static unsigned long count = 0;
  unsigned long endMillis = millis();

  count++;
  sum += endMillis - startMillis;
  float avgLoopTime = (float)sum / (float)count;
  Serial.println(endMillis - startMillis);
  Serial.println(avgLoopTime);
  Serial.println(round(avgLoopTime));
  Serial.println();

  return round(avgLoopTime);
}

int convert24To12Hour(int hour24) {
  int hour12 = hour24 > 12 ? hour24 - 12 : hour24;
  return hour12 == 0 ? 12 : hour12;
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
  long now = millis();
  static long change = now + 1000;

  if (now > change) {
    change = now + 1000;
    colonOn = !colonOn;
  }

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
