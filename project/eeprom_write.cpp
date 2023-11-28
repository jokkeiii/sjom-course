#include <EEPROM.h>

String eepromMessage = "Made by: Arif, Henri ja Jokke";
int address = 0;

void setup() {

  Serial.begin(9600); // serial communication initialize
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB
  }

  // Read the stored value from EEPROM
  int storedValue = EEPROM.read(address);
  // Check if EEPROM has data
  if (storedValue == 255) {
    Serial.println("EEPROM is empty.");
    EEPROM.put(address, eepromMessage);
    Serial.println("String '" + eepromMessage + "' stored successfully.");
  } else {
    EEPROM.get(address, eepromMessage);
    Serial.println(eepromMessage);
  }
}

void loop() {}