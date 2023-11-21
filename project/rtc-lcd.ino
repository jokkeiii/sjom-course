#include "PCF85063TP.h"
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27, 16, 4); // I2C address 0x27, 16 column and 2 rows

PCD85063TP clock; // define a object of PCD85063TP class

void setup() {
  lcd.init(); // initialize the lcd
  lcd.backlight();
  lcd.clear();
  clock.begin();
  // clock.stopClock();
  // clock.fillByYMD(2023, 11, 21); // Jan 19,2013
  // clock.fillByHMS(11, 27, 00);   // 15:28 30"
  // clock.fillDayOfWeek(TUE);      // Saturday
  // clock.setTime();               // write time to the RTC chip
  // clock.startClock();

  // clock.setcalibration(1, 32767.2);  // Setting offset by clock frequency
  uint8_t ret = clock.calibratBySeconds(0, -0.000041);
  lcd.setCursor(0, 0);
  lcd.print(" Time now from RTC: ");
}

void loop() {
  lcdPrintTime();
  delay(1000);
}

// Function: Display time on the lcd
void lcdPrintTime() {
  clock.getTime();

  lcd.setCursor(0, 1);
  lcd.print("      ");
  lcd.print(clock.hour, DEC);
  lcd.print(":");
  lcd.print(clock.minute, DEC);
  lcd.print(":");
  lcd.print(clock.second, DEC);
  lcd.print("      ");

  lcd.setCursor(0, 2);
  lcd.print("     ");
  lcd.print(clock.month, DEC);
  lcd.print("/");
  lcd.print(clock.dayOfMonth, DEC);
  lcd.print("/");
  lcd.print(clock.year + 2000, DEC);
  lcd.print("     ");

  lcd.setCursor(0, 3);
  lcd.print("       ");
  lcd.print(clock.dayOfMonth);
  lcd.print("*");
  switch (clock.dayOfWeek) // Friendly printout the weekday
  {
  case MON:
    lcd.print("MON");
    break;
  case TUE:
    lcd.print("TUE");
    break;
  case WED:
    lcd.print("WED");
    break;
  case THU:
    lcd.print("THU");
    break;
  case FRI:
    lcd.print("FRI");
    break;
  case SAT:
    lcd.print("SAT");
    break;
  case SUN:
    lcd.print("SUN");
    break;
  }
  lcd.print("       ");
}
