#include "PCF85063TP.h"
#include <EEPROM.h>
#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
#include <TimerOne.h>
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
Keypad custom_keypad =
    Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

int eeprom_address = 0;
char custom_key;
volatile bool timer_flag = false;

enum VIEWS { INSTRUCTIONS, MAIN_CLOCK, EEPROM_VIEW };
VIEWS current_view = INSTRUCTIONS;

void instructionsView();
void lcdPrintTime();
void readEeprom();
void timerCallback();

void setup() {
  Serial.begin(115200);
  // watchdog not needed (yet)
  wdt_disable();

  Timer1.attachInterrupt(timerCallback);

  lcd.init();
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
  custom_key = custom_keypad.getKey();
  // Serial.println(custom_key);
  if (custom_key == 'A') {
    lcd.clear();
    current_view = MAIN_CLOCK;
    lcdPrintTime();
  } else if (custom_key == 'B') {
    current_view = EEPROM_VIEW;
    readEeprom();
  } else if (custom_key == '#') {
    current_view = INSTRUCTIONS;
    instructionsView();
  } else if (current_view == MAIN_CLOCK) {
    current_view = MAIN_CLOCK;
    lcdPrintTime();
  } else if (!timer_flag && current_view != INSTRUCTIONS) {
    lcd.clear();
    current_view = INSTRUCTIONS;
    instructionsView();
  }
}

// startup view
void instructionsView() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("    Hello there!");
  lcd.setCursor(0, 1);
  lcd.print(" Main clock with A");
  lcd.setCursor(0, 2);
  lcd.print("    EEPROM with B");
  lcd.setCursor(0, 3);
  lcd.print("  Press key to go!");
}

// display current time on the lcd
void lcdPrintTime() {
  lcd.setCursor(0, 0);
  lcd.print(" Time now from RTC: ");

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
  lcd.print("       ");
  if (clock.dayOfMonth < 10) {
    lcd.print("0");
  }
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
}

// read EEPROM and write it to the lcd
void readEeprom() {
  int eeprom_message_length = 0;

  lcd.clear();
  lcd.home();
  lcd.print("      EEPROM:");

  for (unsigned int i = 0; i < EEPROM.length(); i++) {
    int byte = EEPROM.read(i);
    if (byte == 255) {
      break;
    }
    eeprom_message_length++;
  }

  lcd.setCursor(0, 1);

  // Read chars from EEPROM and print them
  for (int i = 0; i < eeprom_message_length; i++) {
    char ch = EEPROM.read(i);

    if (i == 9) {
      lcd.setCursor(0, 2);
    }
    lcd.print(ch);
  }

  Timer1.initialize(3000000); // 10 seconds in microseconds
  timer_flag = true;
}

// timer1 ISR callback
void timerCallback() {
  Timer1.stop();
  timer_flag = false;
}