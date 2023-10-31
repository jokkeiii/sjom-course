#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;

const int colorR = 255;
const int colorG = 0;
const int colorB = 0;

void setup()
{
    // set up the LCD's number of columns and rows:
    lcd.begin(16, 2);

    // init rgb
    lcd.setRGB(colorR, colorG, colorB);

    // set lcd cursor to row 0 col 0
    lcd.setCursor(0, 0);

    Serial.begin(9600);
    Serial.println("Write something to the serial monitor.");
}

void loop()
{
    // check if serial monitor is connected
    if (Serial.available() > 0)
    {
        // read the serail message
        String message = Serial.readStringUntil('\n');
        Serial.print("Message received, content: ");
        Serial.println(message);
        // find the index of specified submessage
        int pos_s = message.indexOf("Print");
        int pos_l = message.indexOf("LCD");

        // if print command was found
        if (pos_s > -1)
        {
            Serial.println("Command = Print ");
            // find the index of the start of message
            pos_s = message.indexOf(":");

            // if message was found
            if (pos_s > -1)
            {
                // find the message and print stuff
                String stat = message.substring(pos_s + 1);
                if (stat == "Hi" || "hi")
                {
                    Serial.println("Hi!");
                }
                else if (stat == "Hello")
                {
                    Serial.println("Hello there!");
                }
            }
        }
        // if lcd command was found
        else if (pos_l > -1)
        {
            Serial.println("Command = LCD ");

            // find the start of message
            pos_l = message.indexOf(":");
            String end_message = message.substring(pos_l + 1);

            // print the message to lcd
            lcd.print(end_message);
            // set remaing columns as empty
            lcd.print("                ");
        }
        else
        {
            Serial.println("No greeting found, try typing Print:Hi or Print:Hello\n");
        }
    }

    // set cursor back to start of lcd
    lcd.setCursor(0, 0);
}