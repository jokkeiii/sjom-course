const int ledPin = 13;
volatile byte ledState = HIGH;
volatile unsigned int counter = 0;

void setup()
{
    pinMode(ledPin, OUTPUT);
    cli(); // Disable global interrupts

    TCNT2 = 0;  // Initialize Timer2 counter value to 0
    TCCR2A = 0; // Set Timer2 to normal mode
    TCCR2B = 0; // Clear settings

    // Prescaler = 64
    TCCR2B = (1 << CS22);

    TIFR2 = (1 << TOV2);   // Clear overflow flag
    TIMSK2 = (1 << TOIE2); // Enable Timer2 overflow interrupt

    sei(); // Enable global interrupts
}

ISR(TIMER2_OVF_vect) // ISR for Timer2 overflow
{
    counter++;           // Increment counter
    if (counter >= 1953) // Approximately 1 second; Adjust as needed
    {
        counter = 0;
        ledState = !ledState; // Toggle LED
    }
}

void loop()
{
    digitalWrite(ledPin, ledState); // Update LED state based on ledState variable
}
