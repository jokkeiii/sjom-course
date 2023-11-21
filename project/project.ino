// Include necessary libraries for I2C and LCD
#include "rgb_lcd.h"
#include <Wire.h>

rgb_lcd lcd;

// white blue lcd
const int colorR = 255;
const int colorG = 0;
const int colorB = 0;



void setup() {
  lcd.begin(16, 2);
  lcd.setRGB(colorR, colorG, colorB);
  lcd.setCursor(0, 0);

  Serial.begin(9600);
  Serial.println("Here:");
  lcd.setCursor(0, 0);
  lcd.print("A:Set main time ");
}

void mainClockView() {

}

void timerView() {

}

void setupView() {
    
}


void loop() {



}
