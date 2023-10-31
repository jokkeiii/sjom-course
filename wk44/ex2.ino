// read color sensor values and write them to lcd

#include <Wire.h>
#include "rgb_lcd.h"
#include "DFRobot_TCS34725.h"

DFRobot_TCS34725 tcs = DFRobot_TCS34725(&Wire, TCS34725_ADDRESS, TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

rgb_lcd lcd;

const int colorR = 255;
const int colorG = 0;
const int colorB = 0;

void setup()
{
    // start color sensor
    tcs.begin();

    // set up the LCD's number of columns and rows:
    lcd.begin(16, 2);

    // init rgb
    lcd.setRGB(colorR, colorG, colorB);

    // set lcd cursor to row 0 col 0
    lcd.setCursor(0, 0);

    delay(1000);
}

void loop()
{

    lcd.setCursor(0, 0);
    uint16_t clear, red, green, blue;
    // read the sensor color values
    tcs.getRGBC(&red, &green, &blue, &clear);
    // turn off LED
    tcs.lock();

    // Figure out some basic hex code for visualization
    uint32_t sum = clear;
    float r, g, b;
    r = red;
    r /= sum;
    g = green;
    g /= sum;
    b = blue;
    b /= sum;
    r *= 256;
    g *= 256;
    b *= 256;

    // print the clear values and rgb hex values
    lcd.print((int)clear);
    lcd.print(" ");
    lcd.print((int)r);
    lcd.print(" ");
    lcd.print((int)g);
    lcd.print(" ");
    lcd.print((int)b);
    // set remaining columns as empty
    lcd.print("     ");

    delay(10);
}
