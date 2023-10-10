// Polling Timer/Counter2 Overflow
// The code snippet utilizes Timer/Counter2 overflow interrupt to toggle an LED.

// LED connected to digital pin 13
const int ledPin = 13;
// Initial LED state (ON)
byte ledState = HIGH;
// Counter for overflow events
int count = 0;

void setup()
{
    // Set the LED pin as an output
    pinMode(ledPin, OUTPUT);

    // Initialize Timer/Counter2 value to 0
    TCNT2 = 0x00;
    // Clear Timer/Counter Control Register A
    TCCR2A = 0x00;
    // Set clock prescaler
    TCCR2B |= (1 << CS22) | (1 << CS21) | (1 << CS20);
    // Clear the Timer/Counter2 Overflow Flag
    TIFR2 |= (1 << TOV2);
}

void loop()
{
    // Check if Timer/Counter2 Overflow Flag is set
    if (TIFR2 & B001)
    {
        // Increment overflow counter
        count++;
        // Clear the overflow flag
        TIFR2 = (1 << TOV2);
    }

    // If 50 overflows have occurred
    if (count == 50)
    {
        // Toggle LED state
        ledState = !ledState;
        // Update LED state
        digitalWrite(ledPin, ledState);
        // Reset overflow counter
        count = 0;
    }
}
