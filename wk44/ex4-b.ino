// Include necessary libraries for I2C and LCD
#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd; // Create an LCD object

// Define pin numbers for LEDs
const int green_led = 9;
const int red_led = 10;

// Define RGB color values for LCD
const int colorR = 255;
const int colorG = 0;
const int colorB = 0;

int wrong_count = 0; // Counter for incorrect pin entries

// Define a function that implements a 10-second wait
void wait_10()
{
    unsigned long start_time = millis(), current_time; // Initialize timing variables
    int countdown = 10, count_up = 0;                  // Set up countdown from 10 seconds
    lcd.setCursor(0, 1);                               // Position the cursor on the LCD
    lcd.print("                ");                     // Clear the second row of the LCD

    // Loop to update countdown every second
    while (countdown > 0)
    {
        current_time = millis();
        if (current_time - start_time >= count_up * 1000)
        {
            lcd.setCursor(0, 1);          // Reposition cursor
            lcd.print("Odota ");          // Print "Wait" in Finnish
            lcd.print(countdown);         // Show the countdown
            lcd.print("               "); // Clear the rest of the line
            count_up++;
            countdown--;
        }
    }

    delay(1000);                         // Wait for an additional second
    lcd.setCursor(0, 1);                 // Reposition cursor
    lcd.print("Anna pin-koodi...     "); // Prompt for pin code
}

void setup()
{
    lcd.begin(16, 2);                   // Initialize the LCD to 16 columns and 2 rows
    lcd.setRGB(colorR, colorG, colorB); // Set the LCD backlight color
    lcd.setCursor(0, 0);                // Set cursor to the beginning of first line

    Serial.begin(9600);                                       // Start serial communication at 9600 baud rate
    Serial.println("Write something to the serial monitor."); // Print to the serial monitor

    pinMode(green_led, OUTPUT); // Set the green LED pin as output
    pinMode(red_led, OUTPUT);   // Set the red LED pin as output
}

void loop()
{
    if (Serial.available() > 0) // Check if there's data from the serial port
    {
        String message = Serial.readStringUntil('\n'); // Read the incoming message until newline
        Serial.print("Message received, content: ");
        Serial.println(message); // Print the received message

        // Find the position of keywords in the message
        int pos_s = message.indexOf("Print");
        int pos_l = message.indexOf("LCD");
        int pos_p = message.indexOf("PIN");

        if (pos_s > -1) // If "Print" is found in the message
        {
            Serial.println("Command = Print ");
            pos_s = message.indexOf(":"); // Find the colon indicating the start of the message
            if (pos_s > -1)
            {
                String stat = message.substring(pos_s + 1); // Extract the actual message
                // Respond to specific greetings
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
        else if (pos_l > -1 | pos_p > -1) // If "LCD" or "PIN" is found in the message
        {
            String end_message; // Variable to hold the extracted message
            // Extract the message for LCD command
            if (pos_l > -1)
            {
                Serial.println("Command = LCD ");
                pos_l = message.indexOf(":");
                end_message = message.substring(pos_l + 1);
            }
            // Extract the message for PIN command
            else
            {
                Serial.println("Command = PIN ");
                pos_p = message.indexOf(":");
                end_message = message.substring(pos_p + 1);
            }

            // Check the extracted message and perform actions accordingly
            if (end_message == "Lukittu") // If the message is "Locked"
            {
                digitalWrite(red_led, HIGH);  // Turn on the red LED
                digitalWrite(green_led, LOW); // Turn off the green LED
                // Display "LOCKED" on the LCD
                lcd.setCursor(0, 0);
                lcd.print(" LUKITTU! ");
                lcd.setCursor(0, 1);
                lcd.print("Anna pin-koodi...");
            }
            else if (end_message == "password") // If the message is "password"
            {
                digitalWrite(red_led, LOW);    // Turn off the red LED
                digitalWrite(green_led, HIGH); // Turn on the green LED
                // Display "Unlocked" on the LCD
                lcd.setCursor(0, 0);
                lcd.print(" Avattu! ");
                lcd.setCursor(0, 1);
                lcd.print("                ");
            }
            else // If the message is neither "Locked" nor "password"
            {
                wrong_count++;                // Increment the wrong attempt counter
                digitalWrite(red_led, HIGH);  // Turn on the red LED
                digitalWrite(green_led, LOW); // Turn off the green LED
                // Display "LOCKED" and the wrong attempt count on the LCD
                lcd.setCursor(0, 0);
                lcd.print(" LUKITTU! ");
                lcd.setCursor(0, 1);
                lcd.print("Pin vaarin X");
                lcd.print(wrong_count);
                lcd.print("                ");

                if (wrong_count == 3) // If the wrong attempt count reaches 3
                {
                    delay(500);
                    wrong_count = 0; // Reset the wrong attempt counter
                    wait_10();       // Call the wait function
                }
            }
        }
        else // If no recognizable command was found
        {
            Serial.println("No greeting found, try typing Print:Hi or Print:Hello\n");
        }
    }
}
