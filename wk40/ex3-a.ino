int sensorPin = A7;
int ledPin = 9;
int sensorValue = 0;
int val;
int ledState = LOW;

void setup()
{
    Serial.begin(9600);
    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, LOW);
    ADC_init();
}

void loop()
{
    uint16_t sensorValue = ADC_read(A7);
    Serial.println(sensorValue);
    analogWrite(ledPin, sensorValue / 4);
    delay(300);
}

void ADC_init()
{
    // rekisteriasetukset
    ADMUX |= (1 << REFS0) | (1 << MUX2) | (1 << MUX1) | (1 << MUX0);
    ADCSRA |= (1 << ADEN);
    ADCSRB = 0x00;
}

uint16_t ADC_read(uint8_t ch)
{
    // aloitetaan muunnos
    ADCSRA |= (1 << ADSC);
    Serial.println(ADCSRA, BIN);

    while (ADCSRA & B01000000)
    {
        ;
    }
    Serial.println(ADCSRA, BIN);

    val = ADC;
    return val;
}