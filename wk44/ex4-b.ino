#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;

const int green_led = 9;
const int red_led = 10;
const int colorR = 255;
const int colorG = 0;
const int colorB = 0;
int wrong_count = 0;

void wait_10()
{
    unsigned long start_time = millis(), current_time;
    int countdown = 10, count_up = 0;
    lcd.setCursor(0, 1);
    lcd.print("                ");

    while (countdown > 0)
    {
        current_time = millis();
        if (current_time - start_time >= count_up * 1000)
        {
            lcd.setCursor(0, 1);
            lcd.print("Odota ");
            lcd.print(countdown);
            lcd.print("               ");
            count_up++;
            countdown--;
        }
    }

    delay(1000);
    lcd.setCursor(0, 1);
    lcd.print("Anna pin-koodi...     ");
}

void setup()
{
    // set up the LCD's number of columns and rows:
    lcd.begin(16, 2);
    // init rgb
    lcd.setRGB(colorR, colorG, colorB);
    // set lcd cursor to row 0 col 0
    lcd.setCursor(0, 0);

    // Set Serial for printing
    Serial.begin(9600);
    Serial.println("Write something to the serial monitor.");

    // Set Pins for output
    pinMode(green_led, OUTPUT);
    pinMode(red_led, OUTPUT);
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
        int pos_p = message.indexOf("PIN");

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
        else if (pos_l > -1 | pos_p > -1)
        {
            String end_message;
            if (pos_l > -1)
            {
                Serial.println("Command = LCD ");
                // find the start of message
                pos_l = message.indexOf(":");
                end_message = message.substring(pos_l + 1);
            }
            else
            {
                Serial.println("Command = PIN ");
                // find the start of message
                pos_p = message.indexOf(":");
                end_message = message.substring(pos_p + 1);
            }

            // Check message and work accordingly
            if (end_message == "Lukittu")
            {
                // Write to pins
                digitalWrite(red_led, HIGH);
                digitalWrite(green_led, LOW);
                // Write to screen
                lcd.setCursor(0, 0);
                lcd.print(" LUKITTU! ");
                lcd.setCursor(0, 1);
                lcd.print("Anna pin-koodi...");
            }
            else if (end_message == "password")
            {
                // Write to pins
                digitalWrite(red_led, LOW);
                digitalWrite(green_led, HIGH);
                // Write to screen
                lcd.setCursor(0, 0);
                lcd.print(" Avattu! ");
                lcd.setCursor(0, 1);
                lcd.print("                ");
            }
            else
            {
                wrong_count++;
                // Write to pins
                digitalWrite(red_led, HIGH);
                digitalWrite(green_led, LOW);
                // Write to screen
                lcd.setCursor(0, 0);
                lcd.print(" LUKITTU! ");
                lcd.setCursor(0, 1);
                lcd.print("Pin vaarin X");
                lcd.print(wrong_count);
                lcd.print("                ");

                if (wrong_count == 3)
                {
                    delay(500);
                    wrong_count = 0;
                    wait_10();
                }
            }
        }
        else
        {
            Serial.println("No greeting found, try typing Print:Hi or Print:Hello\n");
        }
    }
}
