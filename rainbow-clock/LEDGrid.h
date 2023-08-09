class LEDGrid {
private:
  int _width;
  int _height;
  int _startPixel = BOTTOM_LEFT;
  CRGB *_leds;

public:
  static constexpr int BOTTOM_LEFT = 0;
  static constexpr int TOP_LEFT = 1;

  LEDGrid(int width, int height, int startPixel) {
    _width = width;
    _height = height;
    _startPixel = startPixel;
    _leds = new CRGB[_width * _height];
  }

  struct CRGB *operator[](int i) {
    return (&_leds[i]);
  }

  struct CRGB &operator()(int x, int y) {
    return _leds[xyCoordsToIndex(x, y)];
  }

  int xyCoordsToIndex(int x, int y) {
    // convert x, y coordinates to an index on the one-dimensional array that
    // snakes back and forth on the grid
    switch (_startPixel) {
    case BOTTOM_LEFT:
      if (y % 2 == 0) {
        return y * _width + x;
      } else {
        return y * _width + (_width - x - 1);
      }
    case TOP_LEFT:
      if (y % 2 == 0) {
        return (_height - y - 1) * _width + x;
      } else {
        return (_height - y - 1) * _width + (_width - x - 1);
      }
    }
  }
};
