#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4); // I2C address 0x27, 20 column and 4 rows

void instructionsView() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Hello!");
    lcd.setCursor(0, 1);
    lcd.print("Clock ready to go!");
    lcd.setCursor(0, 2);
    lcd.print("Navigate with keys");
    lcd.setCursor(0, 3);
    lcd.print("Tap key to go");
}

void setup() {
    lcd.init();
    lcd.backlight();
    instructionsView();
}

void loop {

}