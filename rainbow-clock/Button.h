#include "Timer.h"

#define LONG_PRESS_DURATION 2000 // Hold button for 2 seconds to long press

class Button {

private:
  int _pin;                         // Data pin on the ESP32
  bool _click = false;              // Sets to true when button is clicked
  bool _longPress = false;          // Sets to true when button is lock pressed
  bool _longPressTriggered = false; // Prevents a click from triggering when
                                    // lifting the button up after a long press
  int _prevState = BUTTON_UP;       // The state of the button in the last loop
  Timer _longPressTimer = {LONG_PRESS_DURATION}; // For timing a long press

public:
  static constexpr int BUTTON_DOWN = LOW;
  static constexpr int BUTTON_UP = HIGH;

  Button(int pin) { _pin = pin; }

  void setupButton() { pinMode(_pin, INPUT_PULLUP); }

  bool clicked() { return _click; }

  bool longPressed() { return _longPress; }

  void readState() {
    int state = digitalRead(_pin);
    _click = false;
    _longPress = false;

    if (state == BUTTON_DOWN && _prevState == BUTTON_UP) {
      // If the button is down and was previously up, start a timer
      _longPressTimer.reset();

    } else if (state == BUTTON_DOWN && _longPressTimer.complete()) {
      // If the button is down and the long press duration is reached,
      // a long press has occurred! Trigger the long press by setting the
      // `_longPress` variable to true. Also start the timer over.
      _longPress = true;
      _longPressTimer.reset();
      _longPressTriggered = true; // Set this to true until button is lifted

    } else if (state == BUTTON_UP && _prevState == BUTTON_DOWN) {
      // If the button is up and was previously down, either a click or a long
      // press occurred. Check if a long press already triggered by checking
      // `_longPressTriggered`, and if so, reset it back to default. If a long
      // press was not triggered, trigger a click by setting the `_click`
      // variable to true.
      if (_longPressTriggered) {
        _longPressTriggered = false;
      } else {
        _click = true;
      }
    }

    _prevState = state;
  }
};
