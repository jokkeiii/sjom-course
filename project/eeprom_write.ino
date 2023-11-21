#include <EEPROM.h>


String eepromMessage = "Tekijät: Arif, Henri ja Joakim";
int address = 0;

// values saved in eeprom should never exceed 500 bytes
const int eeprom_size = 500; 
char eeprom_buffer[eeprom_size];

char first_eeprom_value;


void setup() {

    Serial.begin(9600); // serial communication initialize
    while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB
    }

    EEPROM.put(address, eepromMessage);
}

void loop() {
}