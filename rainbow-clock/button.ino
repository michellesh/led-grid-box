void handleButtonState() {
  // Read the value from the data pin
  button.update();

  if (button.longPressed) {
    // Go to next mode when button is long pressed
    c.mode = (c.mode + 1) % NUM_MODES;
  }

  if (button.clicked) {
    // Increment the digit according to which mode we're in
    if (c.mode == EDIT_HOUR) {
      c.hour++;
      c.hour %= 24;
    } else if (c.mode == EDIT_MINUTE_DIGIT_1) {
      c.minute += 10;
      c.minute %= 60;
    } else if (c.mode == EDIT_MINUTE_DIGIT_2) {
      c.minute++;
      if (c.minute % 10 == 0) {
        // If the minute wraps from 9 -> 10, it increments the left minute
        // digit, which was already set in the last edit mode, so subtract 10 to
        // keep the left minute digit the same
        c.minute -= 10;
      }
      c.minute %= 60;
    }

    // Tell the clock object that this is the new time
    if (c.mode != SHOW_TIME) {
      c.setNewTime(c.hour, c.minute);
    }
  }
}
