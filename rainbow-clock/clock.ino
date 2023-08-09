void updateTime() {
  // Update the accurate hour and minute from the RTC module
  // in SHOW_TIME mode only (don't update while setting the clock)
  if (c.mode == SHOW_TIME) {
    c.hour = rtc.getHour(true);
    c.minute = rtc.getMinute();
    c.second = rtc.getSecond();
  }

  // Convert 24-hour time to 12-hour time
  int hour12 = convert24hourTo12hour(c.hour);

  // Separate the hours and minutes into left and right digits
  c.hourDigit1 = hour12 / 10;
  c.hourDigit2 = hour12 % 10;
  c.minuteDigit1 = c.minute / 10;
  c.minuteDigit2 = c.minute % 10;
}

void flashDigits() {
  if (c.mode != SHOW_TIME) {
    // If editing the time, flash the digit being edited every 300ms
    EVERY_N_MILLISECONDS(EDIT_TIME_FLASH_DURATION) {
      c.hideDigit = !c.hideDigit;
      c.hideColon = c.hideDigit;
    }
  } else {
    // If in SHOW_TIME mode, flash the colon every second
    EVERY_N_MILLISECONDS(COLON_FLASH_DURATION) { c.hideColon = !c.hideColon; }
  }
}

int convert24hourTo12hour(int hour24) {
  int hour12 = hour24 > 12 ? hour24 - 12 : hour24;
  return hour12 == 0 ? 12 : hour12;
}
