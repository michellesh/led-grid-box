void readEEPROM() {
  c.hour = EEPROM.read(EEPROM_HOUR);
  c.minute = EEPROM.read(EEPROM_MINUTE);
  c.second = EEPROM.read(EEPROM_SECOND);
  rtc.setTime(c.second, c.minute, c.hour, DAY, MONTH, YEAR);
}

void updateEEPROM() {
  EVERY_N_SECONDS(1) {
    // Save values in EEPROM. Will only be commited if values have changed.
    EEPROM.write(EEPROM_HOUR, rtc.getHour(true));
    EEPROM.write(EEPROM_MINUTE, rtc.getMinute());
    EEPROM.write(EEPROM_SECOND, rtc.getSecond());
    EEPROM.commit();
    Serial.println(rtc.getTime("%H:%M:%S"));
  }
}
