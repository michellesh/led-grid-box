// Modes
#define NUM_MODES 4           // 4 modes
#define SHOW_TIME 0           // Mode 0: show the current time
#define EDIT_HOUR 1           // Mode 1: set the hour digit
#define EDIT_MINUTE_DIGIT_1 2 // Mode 2: set the left minute digit
#define EDIT_MINUTE_DIGIT_2 3 // Mode 3: set the right minite digit

// (The RTC library requires both time and date. Since the clock only tracks
// time, these values don't do anything.)
#define DAY 11
#define MONTH 8
#define YEAR 2023

// Customizable variables
#define EDIT_TIME_FLASH_DURATION 300 // milliseconds per flash when setting time
#define COLON_FLASH_DURATION 1000    // milliseconds per colon flash

// This class stores all clock-related data, and functions to access the
// individual digits and whether they are visible.
class Clock {

private:
  ESP32Time _rtc;

  // When setting the clock, the digit you're currently setting flashes on and
  // off. `_hideDigit` tracks whether the digit being edited is currently hidden
  bool _hideDigit;

  // The colon always flashes every second, unless you're setting the time, it
  // flashes along with the digit being edited
  bool _hideColon;

  // Convert 24-hour time to 12-hour time
  int _get12hour(int hour24) {
    int hour12 = hour24 % 12;
    return hour12 == 0 ? 12 : hour12;
  }

public:
  int mode; // the current mode

  int hour;   // the current hour in 24-hour time
  int minute; // the current minute
  int second; // the current second

  void updateTimeFromRTC() {
    // Update the accurate hour and minute from the RTC module
    // in SHOW_TIME mode only (don't update while setting the clock)
    if (mode == SHOW_TIME) {
      hour = _rtc.getHour(true);
      minute = _rtc.getMinute();
      second = _rtc.getSecond();
    }
  }

  void setNewTime(int newHour, int newMinute, int newSecond = 0) {
    // When finished setting the clock, this function gets called to tell the
    // RTC library the newly set time
    _rtc.setTime(newSecond, newMinute, newHour, DAY, MONTH, YEAR);
  }

// Separate the hours and minutes into left and right digits
int getHourDigit1() { return _get12hour(hour) / 10; }

int getHourDigit2() { return _get12hour(hour) % 10; }

int getMinuteDigit1() { return minute / 10; }

int getMinuteDigit2() { return minute % 10; }

void updateDigitVisibility() {
  // If editing the time, flash the digit being edited every 300ms
  // The `_hideDigit` boolean is toggled every 300ms even when we're not in
  // edit mode. But it knows to only flash the digit in edit mode because
  // the "isDigitVisible" functions below check both the mode and this
  // `_hideDigit` boolean.
  EVERY_N_MILLISECONDS(EDIT_TIME_FLASH_DURATION) { _hideDigit = !_hideDigit; }
}

void updateColonVisibility() {
  // Flash the colon every 1 second
  EVERY_N_MILLISECONDS(COLON_FLASH_DURATION) { _hideColon = !_hideColon; }
}

bool isHourDigit1Visible() {
  // Also hide the left hour digit if it's zero, ie. show 5:00 instead of
  // 05:00
  return getHourDigit1() != 0 && (mode != EDIT_HOUR || !_hideDigit);
}

// This is the same as saying: if we're not editing the hour, return true
// (it's visible). If we are, and `_hideDigit` is false, return true.
// Otherwise, return false.
bool isHourDigit2Visible() { return mode != EDIT_HOUR || !_hideDigit; }

bool isMinuteDigit1Visible() {
  return mode != EDIT_MINUTE_DIGIT_1 || !_hideDigit;
}

bool isMinuteDigit2Visible() {
  return mode != EDIT_MINUTE_DIGIT_2 || !_hideDigit;
}

bool isColonVisible() {
  // The colon flashes at different speeds depending on the mode. When editing
  // the clock, the colon flash aligns with the digit flash. Otherwise, it
  // flashes slower.
  return mode == SHOW_TIME ? !_hideColon : !_hideDigit;
}





};
