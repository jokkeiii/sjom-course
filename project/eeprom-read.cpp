#include <Arduino.h>
#include <EEPROM.h>

void setup() {
  // Initialize Serial for debugging
  Serial.begin(115200);
}

void loop() {
  int eeprom_message_length = 0;

  for (unsigned int i = 0; i < EEPROM.length(); i++) {
    int num = EEPROM.read(i);
    if (num == 255) {
      break;
    }
    eeprom_message_length++;
  }

  // Read chars from EEPROM and print them
  for (int i = 0; i < eeprom_message_length; i++) {
    char ch = EEPROM.read(i);
    Serial.print(ch);
  }
  Serial.println();
}
