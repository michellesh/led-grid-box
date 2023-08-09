void readEEPROM() {
  int hour = EEPROM.read(EEPROM_HOUR);
  int minute = EEPROM.read(EEPROM_MINUTE);
  int second = EEPROM.read(EEPROM_SECOND);
  c.setNewTime(hour, minute, second);
}

void updateEEPROM() {
  EVERY_N_SECONDS(1) {
    // Save values in EEPROM. Will only be commited if values have changed.
    EEPROM.write(EEPROM_HOUR, c.hour);
    EEPROM.write(EEPROM_MINUTE, c.minute);
    EEPROM.write(EEPROM_SECOND, c.second);
    EEPROM.commit();
  }
}
