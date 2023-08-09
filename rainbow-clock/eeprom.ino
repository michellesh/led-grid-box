// EEPROM variables
#define EEPROM_SIZE 3   // 3 bytes stored in EEPROM
#define EEPROM_HOUR 0   // Variable 0: hour
#define EEPROM_MINUTE 1 // Variable 1: minute
#define EEPROM_SECOND 2 // Variable 2: second

void readEEPROM() {
  EEPROM.begin(EEPROM_SIZE);
  int hour = EEPROM.read(EEPROM_HOUR);
  int minute = EEPROM.read(EEPROM_MINUTE);
  int second = EEPROM.read(EEPROM_SECOND);
  c.setNewTime(hour, minute, second);
}

void updateEEPROM() {
  EVERY_N_SECONDS(1) {
    EEPROM.write(EEPROM_HOUR, c.hour);
    EEPROM.write(EEPROM_MINUTE, c.minute);
    EEPROM.write(EEPROM_SECOND, c.second);
    EEPROM.commit();
  }
}
