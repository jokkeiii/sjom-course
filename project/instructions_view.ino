#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4); // I2C address 0x27, 20 column and 4 rows

void instructionsView() {
    lcd.clear();
    lcd.setCursor(0, 1);
    lcf.print("Hello! Your clock is ready to serve.
     Navigate features by pressing keys.)
    lcd.setCursor(0, 3);
    lcd.print("Press to number 1-4 to continue");

}

void setup() {
    instructionsView();
}

void loop {

}