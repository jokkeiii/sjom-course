#include <EEPROM.h>

// EEPROM address to store and retrieve the value
int address = 0;  

void setup() {
  Serial.begin(9600);

  // Read the stored value from EEPROM
  int storedValue = EEPROM.read(address);

  // Check if EEPROM has data
  if (storedValue == 255) {
    Serial.println("EEPROM is empty.");
  } else {
    // EEPROM has data, erase it
    Serial.println("EEPROM has data. Erasing...");
    EEPROM.write(address, 255);
    Serial.println("EEPROM erased successfully.");
  }
}

void loop() {
  // Your loop code...
}
