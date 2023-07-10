#include <FastLED.h>

#define BUTTON_PIN 2
#define LED_PIN 3
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB
#define NUM_LEDS 80
#define BRIGHTNESS 100

CRGB leds[NUM_LEDS];

void setup() {
  Serial.begin(115200);
  delay(500);

  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
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

  for (int i = 0; i < NUM_LEDS; i++) {
    int hue = map(i, 0, NUM_LEDS, 0, 255);
    leds[i] = CHSV(hue, 255, 255);
  }
  FastLED.show();

  delay(100);
}
