void flipHorizontal() {
  swapRows(0, 4);
  swapRows(1, 3);
}

void flipVertical() {
  for (int i = 0; i < WIDTH / 2; i++) {
    swapColumns(i, WIDTH - i - 1);
  }
}

void swapRows(int y1, int y2) {
  CRGB tempRow[WIDTH];
  for (int x = 0; x < WIDTH; x++) {
    tempRow[x] = leds(x, y1);
  }
  for (int x = 0; x < WIDTH; x++) {
    leds(x, y1) = leds(x, y2);
  }
  for (int x = 0; x < WIDTH; x++) {
    leds(x, y2) = tempRow[x];
  }
}

void swapColumns(int x1, int x2) {
  CRGB tempColumn[HEIGHT];
  for (int y = 0; y < HEIGHT; y++) {
    tempColumn[y] = leds(x1, y);
  }
  for (int y = 0; y < HEIGHT; y++) {
    leds(x1, y) = leds(x2, y);
  }
  for (int y = 0; y < HEIGHT; y++) {
    leds(x2, y) = tempColumn[y];
  }
}
