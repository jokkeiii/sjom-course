#include "PCF85063TP.h"
#include <Wire.h>

PCD85063TP clock; // define a object of PCD85063TP class
void setup() {
  Serial.begin(9600);
  clock.begin();
  // clock.stopClock();
  // clock.fillByYMD(2023, 11, 21); // Jan 19,2013
  // clock.fillByHMS(11, 27, 00);   // 15:28 30"
  // clock.fillDayOfWeek(TUE);      // Saturday
  // clock.setTime();               // write time to the RTC chip
  // clock.startClock();

  // clock.setcalibration(1, 32767.2);  // Setting offset by clock frequency
  uint8_t ret = clock.calibratBySeconds(0, -0.000041);
  // Serial.print("offset value: ");
  // Serial.print("0x");
  // Serial.println(ret, HEX);
}
void loop() {
  serialPrintTime();
  delay(1000);
}
/*Function: Display time on the serial monitor*/
void serialPrintTime() {
  clock.getTime();
  Serial.print(clock.hour, DEC);
  Serial.print(":");
  Serial.print(clock.minute, DEC);
  Serial.print(":");
  Serial.print(clock.second, DEC);
  Serial.print("  ");
  Serial.print(clock.month, DEC);
  Serial.print("/");
  Serial.print(clock.dayOfMonth, DEC);
  Serial.print("/");
  Serial.print(clock.year + 2000, DEC);
  Serial.print(" ");
  Serial.print(clock.dayOfMonth);
  Serial.print("*");
  switch (clock.dayOfWeek) // Friendly printout the weekday
  {
  case MON:
    Serial.print("MON");
    break;
  case TUE:
    Serial.print("TUE");
    break;
  case WED:
    Serial.print("WED");
    break;
  case THU:
    Serial.print("THU");
    break;
  case FRI:
    Serial.print("FRI");
    break;
  case SAT:
    Serial.print("SAT");
    break;
  case SUN:
    Serial.print("SUN");
    break;
  }
  Serial.println(" ");
}
