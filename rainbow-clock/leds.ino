#define DIGIT_1_COLUMN 0  // first digit on clock starts in column 0
#define DIGIT_2_COLUMN 4  // second digit on clock starts in column 4
#define DIGIT_3_COLUMN 9  // third digit on clock starts in column 9
#define DIGIT_4_COLUMN 13 // last digit on clock starts in column 13
#define COLON_COLUMN 8    // which column to show the colon in, either 7 or 8

void setClockLEDs() {
  // Set the LEDs for each individual digit, if it's not hidden (ie. if it's
  // not currently flashing in edit mode)

  // Also hide the left hour digit if it's zero, ie. show 5:00 instead of 05:00
  if (c.hourDigit1 != 0 && (c.mode != EDIT_HOUR || !c.hideDigit)) {
    setDigitLEDs(c.hourDigit1, DIGIT_1_COLUMN);
  }
  if (c.mode != EDIT_HOUR || !c.hideDigit) {
    setDigitLEDs(c.hourDigit2, DIGIT_2_COLUMN);
  }
  if (c.mode != EDIT_MINUTE_DIGIT_1 || !c.hideDigit) {
    setDigitLEDs(c.minuteDigit1, DIGIT_3_COLUMN);
  }
  if (c.mode != EDIT_MINUTE_DIGIT_2 || !c.hideDigit) {
    setDigitLEDs(c.minuteDigit2, DIGIT_4_COLUMN);
  }
  setColonLEDs();
}

void setDigitLEDs(int digit, int startColumn) {
  // Get a 3x5 mapping of which pixels to display for this digit
  DigitPixels d = digits[digit];

  // Loop through this 3x5 array pixels and set the LEDs
  for (int x = 0; x < DIGIT_WIDTH; x++) {
    for (int y = 0; y < DIGIT_HEIGHT; y++) {
      // The pixels array tells us to show this LED or set it to Black
      if (d.pixels[y][x]) {
        leds(startColumn + x, y) = getColor(startColumn + x);
      } else {
        leds(startColumn + x, y) = CRGB::Black;
      }
    }
  }
}

CHSV getColor(int column) {
  // Get a color of the rainbow according to which column we're on
  // Map the current column 0 -> 16 to a hue 0 -> 255
  int hue = map(column, 0, WIDTH, 255, 0);
  return CHSV(hue, 255, BRIGHTNESS);
}

void setColonLEDs() {
  // If the colon is flashed on, show the colon LEDs
  if (!c.hideColon) {
    leds(COLON_COLUMN, 1) = CHSV(0, 0, BRIGHTNESS); // White
    leds(COLON_COLUMN, 3) = CHSV(0, 0, BRIGHTNESS); // White
  }
}

void flipVertical() {
  swapRows(0, 4); // Swap the first row and last row
  swapRows(1, 3); // Swap the second row and second-to-last row
  // The middle row stays the same
}

void swapRows(int y1, int y2) {
  // Store the first row values in a temporary variable
  CRGB tempRow[WIDTH];
  for (int x = 0; x < WIDTH; x++) {
    tempRow[x] = leds(x, y1);
  }
  // Fill the first row with the second row values
  for (int x = 0; x < WIDTH; x++) {
    leds(x, y1) = leds(x, y2);
  }
  // Fill the second row with first row values from the temp variable
  for (int x = 0; x < WIDTH; x++) {
    leds(x, y2) = tempRow[x];
  }
}
