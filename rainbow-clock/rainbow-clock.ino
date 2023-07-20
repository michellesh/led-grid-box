/*
 * Rainbow Clock
 * https://github.com/michellesh/rainbow-clock
 */

// Libraries defined here
#include "Button.h"
#include "Clock.h"
#include "DigitPixels.h"

// External libraries
#include <EEPROM.h>    // Built in
#include <ESP32Time.h> // Arduino libraries manager
#include <FastLED.h>   // Arduino libraries manager
#include <LEDMatrix.h> // https://github.com/AaronLiddiment/LEDMatrix

// LED variables
#define LED_PIN 13                // pin D13 on the ESP32
#define BRIGHTNESS 200            // 0-255
#define WIDTH 16                  // number of pixels across
#define HEIGHT 5                  // number of pixels high
#define NUM_LEDS (WIDTH * HEIGHT) // total number of pixels

// Clock variables
// (The RTC library requires both time and date. Since the clock only tracks
// time, these values don't do anything.)
#define DAY 11
#define MONTH 8
#define YEAR 2023

// Modes
#define NUM_MODES 4           // 4 modes
#define SHOW_TIME 0           // Mode 0: show the current time
#define EDIT_HOUR 1           // Mode 1: set the hour digit
#define EDIT_MINUTE_DIGIT_1 2 // Mode 2: set the left minute digit
#define EDIT_MINUTE_DIGIT_2 3 // Mode 3: set the right minite digit

// Button variables
#define BUTTON_PIN 15 // pin D15 on the ESP32

// EEPROM variables
#define EEPROM_SIZE 3   // 3 variables stored in EEPROM
#define EEPROM_HOUR 0   // Variable 0: hour
#define EEPROM_MINUTE 1 // Variable 1: minute
#define EEPROM_SECOND 2 // Variable 2: second

// Customizable variables
#define EDIT_TIME_FLASH_DURATION 300 // millseconds per flash when setting time
#define COLON_FLASH_DURATION 1000    // milliseconds per colon flash

cLEDMatrix<WIDTH, HEIGHT, HORIZONTAL_ZIGZAG_MATRIX> leds;

ESP32Time rtc;

Button button(BUTTON_PIN);

Clock c;

void setup() {
  Serial.begin(115200);
  delay(500);

  // Tell the button object which pin to read from
  button.setupButton();

  // Tell the FastLED library which pin to read from, to use the `leds` array,
  // and how many LEDs there are
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds[0], NUM_LEDS);

  EEPROM.begin(EEPROM_SIZE);

  // Read initial hour/minute from EEPROM
  readEEPROM();
}

void loop() {
  FastLED.clear();

  // Read the button state from the pin and check for a click or a long press
  handleButtonState();

  // Update the hour/minute variables via the RTC module
  updateTime();

  // Store the hour/minute variables in memory
  updateEEPROM();

  // Set the LED pixels to rainbow colored digits
  setClockLEDs();

  // Flash digits when setting the clock
  flashDigits();

  // Since this grid was originally a 16x16 grid that was cut into three 5x16
  // sub-grids, some of the sub-grids have different starting points and
  // different arrangements of LEDs. The back of the grid should have a label
  // indiciating the LED arrangement and if you need to call `flipVertical`
  // Alternatively you can figure out which type of grid you have here:
  // https://github.com/michellesh/rainbow-clock/wiki/LED-grid-layout
  flipVertical();

  // Tell the FastLED library to show your data
  FastLED.show();
}
