#include <Servo.h>

Servo myservo; // Create servo object
int pos = 0;   // Variable to store the servo position

void servo_scaling(int degrees)
{
    // Calculate scaled degrees
    int scaled_degrees = degrees * 0.667;

    // Move servo to degrees
    for (pos = 0; pos <= scaled_degrees; pos += 1)
    {
        myservo.write(pos); // Tell servo to go to position in variable 'pos'
        delay(15);          // Wait 15 ms for the servo to reach the position
    }

    delay(1000);

    // Move servo back to zero degrees
    for (pos = scaled_degrees; pos >= 0; pos -= 1)
    {
        myservo.write(pos); // Tell servo to go to position in variable 'pos'
        delay(15);          // Wait 15 ms for the servo to reach the position
    }
}

void setup()
{
    myservo.attach(9, 400, 2600); // Initialize servo on pin 9 and set pulse width limits to 400-2600 µs
}

void loop()
{
    servo_scaling(90);
    delay(1000); // Pause for 1 second before repeating
}
