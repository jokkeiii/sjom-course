#include <EEPROM.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4); // I2C address 0x27, 20 column and 4 rows

// EEPROM address to store and retrieve the value
int address = 0;
String eepromMessage;

void setupView() {

  int storedValue = EEPROM.read(address);
  if (storedValue == 255) { // An erased EEPROM normally reads as 0xFF
    Serial.println("EEPROM is empty.");
  } else { 
    EEPROM.get(address, eepromMessage);

    Serial.println(eepromMessage);
    lcd.clear()
    String substring1 = eepromMessage.substring(0, 8);
    lcd.setCursor(0, 0);
    lcd.print(substring1);

    lcd.setCursor(0, 1);
    String substring2 = eepromMessage.substring(8);
    lcd.print(substring2);
    
    lcd.print(substring2)
  }
}

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB
  }
  lcd.init();
  lcd.backlight();
  setupView();
}

void loop() {}
  
  
 