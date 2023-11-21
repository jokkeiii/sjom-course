#include <Keypad.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4); // I2C address 0x27, 20 column and 4 rows

int count = 0, row = 0;
const byte ROWS = 4; // four rows
const byte COLS = 4; // four columns
// define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {{'1', '2', '3', 'A'},
                             {'4', '5', '6', 'B'},
                             {'7', '8', '9', 'C'},
                             {'*', '0', '#', 'D'}};

/* on the keyboard the pins from left to right are cols1-4 and then rows1-4
  so the pins from arduino to the keypad (from left to right) are:
  12, 11, 10, 9, 8, 7, 6, 5
*/
byte rowPins[ROWS] = {8, 7, 6, 5}; // connect to the row pinouts of the keypad
byte colPins[COLS] = {12, 11, 10, 9}; // connect to the column pinouts of the
                                      // keypad

// initialize an instance of class NewKeypad
Keypad customKeypad =
    Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

void setup() {
  Serial.begin(9600);
  lcd.init(); // initialize the lcd
  lcd.backlight();
  // clear and set cursor to 0, 0
  lcd.clear();
  lcd.setCursor(0, 0);
}

void loop() {
  char customKey = customKeypad.getKey();

  // if # pressed clear the screen
  if (customKey == '#') {
    lcd.clear();
    count = 0;
    row = 0;

    // if anything else pressed
  } else if (customKey) {
    // check if we have reached the end of row
    if (count == 20) {
      // go to the next row
      row++;
      lcd.setCursor(0, row);
      count = 0;

      // check if we have reached the end of the lcd (20x4)
      if (row >= 4) {
        // go back to 0, 0 and clear screen
        row = 0;
        lcd.setCursor(0, row);
        lcd.clear();
      }
    }

    // after the position checks print the char and increment column count
    lcd.print(customKey);
    count++;
  }
}
