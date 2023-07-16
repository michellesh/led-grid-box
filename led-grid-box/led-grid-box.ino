// clang-format off
#include "Timer.h"
#include "Button.h"
#include "Numbers.h"
#include <EEPROM.h>
#include <ESP32Time.h>
#include <FastLED.h>
#include <LEDMatrix.h>
// clang-format on

#define EEPROM_SIZE 3
#define BUTTON_PIN 15
#define LED_PIN 13
#define BRIGHTNESS 100

#define WIDTH 16
#define HEIGHT 5
#define NUM_LEDS (WIDTH * HEIGHT)
#define COLON_COLUMN 8

#define EEPROM_HOUR 0
#define EEPROM_MINUTE 1
#define EEPROM_SECOND 2

#define DAY 11
#define MONTH 8
#define YEAR 2023

cLEDMatrix<WIDTH, HEIGHT, HORIZONTAL_ZIGZAG_MATRIX> leds;

ESP32Time rtc;

Button button(BUTTON_PIN);

void setup() {
  Serial.begin(115200);
  delay(500);

  button.setupButton();

  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds[0], NUM_LEDS);

  EEPROM.begin(EEPROM_SIZE);

  // Read values from EEPROM
  int hour = EEPROM.read(EEPROM_HOUR);
  int minute = EEPROM.read(EEPROM_MINUTE);
  int second = EEPROM.read(EEPROM_SECOND);

  rtc.setTime(second, minute, hour, DAY, MONTH, YEAR);
}

void loop() {
  FastLED.clear();

  readButtonState();

  int hour = rtc.getHour(true);
  int minute = rtc.getMinute();

  EVERY_N_SECONDS(1) {
    Serial.println(rtc.getTime("%H:%M:%S"));
    // Save values in EEPROM. Will only be commited if values have changed.
    EEPROM.write(EEPROM_HOUR, hour);
    EEPROM.write(EEPROM_MINUTE, minute);
    EEPROM.write(EEPROM_SECOND, rtc.getSecond());
    EEPROM.commit();
  }

  hour = getHour12(hour);
  showTime(hour / 10, hour % 10, minute / 10, minute % 10);

  flipHorizontal();
  // flipVertical();

  FastLED.setBrightness(BRIGHTNESS);
  FastLED.show();

  // delay(1000);
}

void readButtonState() {
  button.readState();
  if (button.clicked()) {
    Serial.println("clicked!");
  }
  if (button.longPressed()) {
    Serial.println("long pressed!");
  }
}

int getHour12(int hour24) {
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
  EVERY_N_SECONDS(1) { colonOn = !colonOn; }
  if (colonOn) {
    leds(COLON_COLUMN, 1) = CHSV(0, 0, BRIGHTNESS); // White
    leds(COLON_COLUMN, 3) = CHSV(0, 0, BRIGHTNESS); // White
  }
}

void showDigit(Digit digit, int startColumn) {
  for (int x = 0; x < DIGIT_WIDTH; x++) {
    for (int y = 0; y < DIGIT_HEIGHT; y++) {
      if (digit.pixels[y][x]) {
        int hue = map(startColumn + x, 0, WIDTH, 255, 0);
        CHSV color = CHSV(hue, 255, BRIGHTNESS);
        leds(startColumn + x, y) = color;
      } else {
        leds(startColumn + x, y) = CRGB::Black;
      }
    }
  }
}
