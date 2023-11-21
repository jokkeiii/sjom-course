#include <EEPROM.h>

// EEPROM address to store and retrieve the value
int address = 0;
String eepromMessage;

void setupView() {

  int storedValue = EEPROM.read(address);
  if (storedValue == 255) { // An erased EEPROM normally reads as 0xFF
    Serial.println("EEPROM is empty.");
  } else {
    //Tämän tilalle tulostus näytölle
    
    EEPROM.get(address, eepromMessage);
    Serial.println(eepromMessage);
  }
}

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB
  }
  setupView();
}

void loop() {}
  
  
 