#include <Arduino.h>
#include <EEPROM.h>

void setup() { Serial.begin(115200); }

void loop() {
  for (unsigned int address = 0; address < EEPROM.length(); address++) {
    byte value = EEPROM.read(address);
    if (value != 255) {
      // 255 is the default value for an uninitialized EEPROM location
      Serial.print("Address ");
      Serial.print(address);
      Serial.print(": ");
      Serial.println(value);
    }
  }
  delay(10000); // Delay for readability (adjust as needed)
}
