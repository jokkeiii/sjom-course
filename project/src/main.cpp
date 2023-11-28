#include "PCF85063TP.h"
#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <avr/wdt.h>

// LCD object
LiquidCrystal_I2C lcd(0x27, 16, 4); // I2C address 0x27, 16 column and 2 rows

// define clock object for RTC
PCD85063TP clock;

const byte ROWS = 4; // four rows
const byte COLS = 4; // four columns

// define the symbols on the buttons of the keypads
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

int touch_sensor_pin = 2;

void instructionsView();
void lcdPrintTime();
void stopTimer();

void setup() {
  Serial.begin(115200);
  // watchdog not needed (yet)
  wdt_disable();

  // touch sensor ISR
  pinMode(touch_sensor_pin, INPUT);
  attachInterrupt(digitalPinToInterrupt(touch_sensor_pin), stopTimer, RISING);

  lcd.init(); // initialize the lcd
  lcd.clear();
  // backlight draws a lot of power so use with caution
  // lcd.backlight();
  clock.begin();

  // set current correct time,
  // if the module has a battery, this is a one time operation
  // clock.stopClock();
  // clock.fillByYMD(2023, 11, 28); // yyyy:mm:dd
  // clock.fillByHMS(11, 03, 00);   // hh:mm:ss
  // clock.fillDayOfWeek(TUE);      // 3 letter weekday
  // clock.setTime();               // write time to the RTC chip
  // clock.startClock();
  // Setting offset by module's clock frequency, 32.768 kHz
  // clock.setcalibration(1, 32768);

  uint8_t ret = clock.calibratBySeconds(0, -0.000041);

  // if calibration failed, do a reset
  if (ret) {
    Serial.println("RTC calibrated successfully!");
  } else {
    Serial.println("RTC calibration failed!");
    // enable watchdog with 15ms
    wdt_enable(WDTO_15MS);
    // infinite loop to trigger the watchdog
    while (1) {
    };
  }

  // show instruction screen
  instructionsView();
}

void loop() {
  char custom_key = customKeypad.getKey();

  switch (custom_key) {
  case '*':
    Serial.println("Screen change!");
    break;
  case '#':
    countdownTimer();
    break;
  default:
    lcd.setCursor(0, 0);
    lcd.print(" Time now from RTC: ");
    lcdPrintTime();
    break;
  }
}

// Function: Display time on the lcd
void lcdPrintTime() {
  clock.getTime();

  lcd.setCursor(0, 1);
  lcd.print("      ");
  // leading zero if number is under 10
  if (clock.hour < 10) {
    lcd.print("0");
  }
  lcd.print(clock.hour, DEC);
  lcd.print(":");

  // leading zero if number is under 10
  if (clock.minute < 10) {
    lcd.print("0");
  }
  lcd.print(clock.minute, DEC);
  lcd.print(":");

  // leading zero if number is under 10
  if (clock.second < 10) {
    lcd.print("0");
  }
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
  lcd.print("< *    ");
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
  lcd.print("    # >");
}

void instructionsView() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("    Hello there!");
  lcd.setCursor(0, 1);
  lcd.print("   Go left with *");
  lcd.setCursor(0, 2);
  lcd.print("   Go right with #");
  lcd.setCursor(0, 3);
  lcd.print(" Tap any key to go!");

  // wait for the user to press a key
  while (true) {
    char custom_key = customKeypad.getKey();

    if (custom_key) {
      break;
    }
  }
}

void stopTimer() {}

void countdownTimer() {
  lcd.clear();
  lcd.home();

  lcd.print("  Countdown timer:  ");
  lcd.setCursor(0, 1);
  lcd.print()
}