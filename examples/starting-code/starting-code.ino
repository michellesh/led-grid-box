#include <FastLED.h> // Arduino libraries manager

#include "LEDGrid.h"

#define LED_PIN 13                // pin D13 on the ESP32
#define WIDTH 16                  // number of pixels across
#define HEIGHT 5                  // number of pixels high
#define NUM_LEDS (WIDTH * HEIGHT) // total number of pixels

// Since this grid was originally a 16x16 grid that was cut into three 5x16
// sub-grids, each sub-grid has two possible LED arrangements. The first pixel
// will either be on the TOP_LEFT or BOTTOM_LEFT (looking at the front of the
// pixels). For diagrams and photos of the different arrangements go here:
// https://github.com/michellesh/rainbow-clock/wiki/LED-grid-layout
// Or you could just try both and see which one works! :)
#define START_PIXEL LEDGrid::TOP_LEFT

LEDGrid leds(WIDTH, HEIGHT, START_PIXEL);

void setup() {
  // Tell the FastLED library which pin to read from, to use the `leds` array,
  // and how many LEDs there are
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds[0], NUM_LEDS);
}

void loop() {
  FastLED.clear(); // Set all LEDs to black

  // ... code here ...

  FastLED.show(); // Tell FastLED to show your data
}
