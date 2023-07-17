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

#define SHOW_TIME 0
#define SET_HOUR 1
#define SET_MINUTE_DIGIT_1 2
#define SET_MINUTE_DIGIT_2 3
#define NUM_MODES 4

#define SET_TIME_FLASH_DURATION                                                \
  300 // How many millseconds per flash when setting time
#define COLON_FLASH_DURATION 1000 // How many milliseconds per colon flash

cLEDMatrix<WIDTH, HEIGHT, HORIZONTAL_ZIGZAG_MATRIX> leds;

ESP32Time rtc;

Button button(BUTTON_PIN);

int mode = SHOW_TIME;
bool hourDigitVisible = true;
bool minuteDigit1Visible = true;
bool minuteDigit2Visible = true;

int hour = 0;
int minute = 0;
int second = 0;

void setup() {
  Serial.begin(115200);
  delay(500);

  button.setupButton();

  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds[0], NUM_LEDS);

  EEPROM.begin(EEPROM_SIZE);

  // Read values from EEPROM
  hour = EEPROM.read(EEPROM_HOUR);
  minute = EEPROM.read(EEPROM_MINUTE);
  second = EEPROM.read(EEPROM_SECOND);

  rtc.setTime(second, minute, hour, DAY, MONTH, YEAR);
}

void loop() {
  FastLED.clear();

  readButtonState();

  updateEEPROM();

  EVERY_N_MILLISECONDS(SET_TIME_FLASH_DURATION) {
    if (mode == SHOW_TIME) {
      hourDigitVisible = true;
      minuteDigit1Visible = true;
      minuteDigit2Visible = true;
    } else if (mode == SET_HOUR) {
      hourDigitVisible = !hourDigitVisible;
      minuteDigit1Visible = true;
      minuteDigit2Visible = true;
    } else if (mode == SET_MINUTE_DIGIT_1) {
      hourDigitVisible = true;
      minuteDigit1Visible = !minuteDigit1Visible;
      minuteDigit2Visible = true;
    } else if (mode == SET_MINUTE_DIGIT_2) {
      hourDigitVisible = true;
      minuteDigit1Visible = true;
      minuteDigit2Visible = !minuteDigit2Visible;
    }
  }

  if (mode == SHOW_TIME) {
    hour = rtc.getHour(true);
    minute = rtc.getMinute();
  }

  int hour12 = getHour12(hour); // Convert 24-hour time to 12-hour time
  showTime(hour12 / 10, hour12 % 10, minute / 10, minute % 10);

  flipHorizontal();
  // flipVertical();

  FastLED.setBrightness(BRIGHTNESS);
  FastLED.show();
}

void readButtonState() {
  button.readState();
  if (button.clicked()) {
    Serial.println("click!");
    if (mode == SET_HOUR) {
      hour++;
      hour %= 24;
    } else if (mode == SET_MINUTE_DIGIT_1) {
      minute += 10;
      minute %= 60;
    } else if (mode == SET_MINUTE_DIGIT_2) {
      minute++;
      if (minute % 10 == 0) {
        minute -= 10;
      }
      minute %= 60;
    }
    rtc.setTime(0, minute, hour, DAY, MONTH, YEAR);
  }
  if (button.longPressed()) {
    Serial.println("long press!");
    mode = (mode + 1) % NUM_MODES; // Increment mode
  }
}

void updateEEPROM() {
  EVERY_N_SECONDS(1) {
    // Save values in EEPROM. Will only be commited if values have changed.
    EEPROM.write(EEPROM_HOUR, rtc.getHour(true));
    EEPROM.write(EEPROM_MINUTE, rtc.getMinute());
    EEPROM.write(EEPROM_SECOND, rtc.getSecond());
    EEPROM.commit();
    Serial.println(rtc.getTime("%H:%M:%S"));
  }
}

void showTime(int hourDigit1, int hourDigit2, int minuteDigit1,
              int minuteDigit2) {
  if (hourDigit1 != 0 && hourDigitVisible) {
    showDigit(digits[hourDigit1], 0);
  }
  if (hourDigitVisible) {
    showDigit(digits[hourDigit2], 4);
  }
  if (minuteDigit1Visible) {
    showDigit(digits[minuteDigit1], 9);
  }
  if (minuteDigit2Visible) {
    showDigit(digits[minuteDigit2], 13);
  }
  showColon();
}

void showColon() {
  static bool colonOn = true;
  EVERY_N_MILLISECONDS(COLON_FLASH_DURATION) {
    if (mode == SHOW_TIME) {
      colonOn = !colonOn;
    }
  }
  EVERY_N_MILLISECONDS(SET_TIME_FLASH_DURATION) {
    if (mode != SHOW_TIME) {
      colonOn = !colonOn;
    }
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
        int hue = map(startColumn + x, 0, WIDTH, 255, 0);
        CHSV color = CHSV(hue, 255, BRIGHTNESS);
        leds(startColumn + x, y) = color;
      } else {
        leds(startColumn + x, y) = CRGB::Black;
      }
    }
  }
}
