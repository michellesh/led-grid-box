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
  EVERY_N_MILLISECONDS(EDIT_TIME_FLASH_DURATION) {
    // Toggle the visibility of the digit depending on the current mode
    switch (c.mode) {
    case EDIT_HOUR:
      c.hideHourDigit = !c.hideHourDigit;
      c.hideMinuteDigit1 = false;
      c.hideMinuteDigit2 = false;
      break;
    case EDIT_MINUTE_DIGIT_1:
      c.hideHourDigit = false;
      c.hideMinuteDigit1 = !c.hideMinuteDigit1;
      c.hideMinuteDigit2 = false;
      break;
    case EDIT_MINUTE_DIGIT_2:
      c.hideHourDigit = false;
      c.hideMinuteDigit1 = false;
      c.hideMinuteDigit2 = !c.hideMinuteDigit2;
      break;
    default: // SHOW_TIME mode, show all digits
      c.hideHourDigit = false;
      c.hideMinuteDigit1 = false;
      c.hideMinuteDigit2 = false;
      break;
    }
  }
}

int convert24hourTo12hour(int hour24) {
  int hour12 = hour24 > 12 ? hour24 - 12 : hour24;
  return hour12 == 0 ? 12 : hour12;
}
