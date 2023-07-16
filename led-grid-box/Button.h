#define LONG_PRESS_DURATION 2000 // Hold button for 2 seconds to long press

class Button {

private:
  int _pin;
  bool _clicked = false;
  bool _longPressed = false;
  int _prevState = BUTTON_UP;
  Timer _longPressTimer = {LONG_PRESS_DURATION};

public:
  static constexpr int BUTTON_DOWN = LOW;
  static constexpr int BUTTON_UP = HIGH;

  Button(int pin) { _pin = pin; }

  void setupButton() { pinMode(_pin, INPUT_PULLUP); }

  void readState() {
    int state = digitalRead(_pin);
    _clicked = false;
    _longPressed = false;

    if (state == BUTTON_DOWN && _prevState == BUTTON_UP) {
      _longPressTimer.reset();
    }

    if (state == BUTTON_UP && _prevState == BUTTON_DOWN) {
      if (_longPressTimer.complete()) {
        _longPressed = true;
      } else {
        _clicked = true;
      }
    }

    _prevState = state;
  }

  bool clicked() { return _clicked; }

  bool longPressed() { return _longPressed; }
};
