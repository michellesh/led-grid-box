#include "Timer.h"

#define LONG_PRESS_DURATION 2000 // Hold button for 2 seconds to long press

class Button {

private:
  int _pin;                         // Data pin on the ESP32
  bool _longPressTriggered = false; // Prevents a click from triggering when
                                    // lifting the button up after a long press
  int _prevState = BUTTON_UP;       // The state of the button in the last loop
  Timer _longPressTimer = {LONG_PRESS_DURATION}; // For timing a long press

public:
  static constexpr int BUTTON_DOWN = LOW;
  static constexpr int BUTTON_UP = HIGH;

  bool clicked = false;     // Sets to true when button is clicked
  bool longPressed = false; // Sets to true when button is lock pressed

  Button(int pin) { _pin = pin; }

  void setupButton() { pinMode(_pin, INPUT_PULLUP); }

  void update() {
    int state = digitalRead(_pin); // Read the signal from the pin

    // Reset the click and long press status
    clicked = false;
    longPressed = false;

    if (state == BUTTON_DOWN && _prevState == BUTTON_UP) {
      // The button is down and was previously up: Could be a click or a long
      // press. Start a timer.
      _longPressTimer.reset();

    } else if (state == BUTTON_DOWN && _longPressTimer.complete()) {
      // The button is down and it's been down for 2 seconds: Trigger a long
      // press by setting the `longPressed` variable to true. Also start the
      // timer over.
      longPressed = true;
      _longPressTimer.reset();
      _longPressTriggered = true; // Set this to true until button is lifted

    } else if (state == BUTTON_UP && _prevState == BUTTON_DOWN) {
      // The button is up and was previously down: Trigger a click. Unless it's
      // the user releasing the button after just long pressing. In that case,
      // don't trigger a click. Check if it was a long press by checking
      // `_longPressTriggered`, and if so, reset it back to default. If it
      // wasn't a long press, trigger a click by setting the `clicked` variable
      // to true.
      if (_longPressTriggered) {
        _longPressTriggered = false;
      } else {
        clicked = true;
      }
    }

    _prevState = state;
  }
};
