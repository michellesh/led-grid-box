// Make a struct to store all the clock related data
struct Clock {
  int mode;

  int hour;   // the current hour in 24-hour time
  int minute; // the current minute
  int second; // the current second

  int hourDigit1;   // the left hour digit. eg. 1 for 12:00pm
  int hourDigit2;   // the right hour digit. eg. 2 for 12:00pm
  int minuteDigit1; // the left minute digit
  int minuteDigit2; // the right minute digit

  // When setting the clock, the digit you're currently setting flashes on and
  // off. `hideDigit` tracks whether the digit being edited is currently hidden
  bool hideDigit;

  // The colon always flashes every second, unless you're setting the time, it
  // flashes along with the digit being edited
  bool hideColon;
};
