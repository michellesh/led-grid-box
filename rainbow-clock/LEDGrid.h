class LEDGrid {
private:
  int _width;
  int _height;
  int _subgridType;
  CRGB *_leds;

public:
  LEDGrid(int width, int height, int subgridType) {
    _width = width;
    _height = height;
    _subgridType = subgridType;
    _leds = new CRGB[_width * _height];
  }

  struct CRGB *operator[](int i) {
    return (&_leds[i]);
  }

  struct CRGB &operator()(int x, int y) {
    return _leds[getIndex(x, y)];
  }

  int getIndex(int x, int y) {
    // convert a x, y coordinates (row and column) to an index on the
    // one-dimensional array that snakes back and forth on the grid
    switch (_subgridType) {
    case 1:
    case 2:
      if (y % 2 == 0) {
        return y * _width + x;
      } else {
        return y * _width + (_width - x - 1);
      }
    case 3:
      if (y % 2 == 0) {
        return (_height - y - 1) * _width + x;
      } else {
        return (_height - y - 1) * _width + (_width - x - 1);
      }
    }
  }
};
