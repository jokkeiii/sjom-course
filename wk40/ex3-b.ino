int sensorPin = A4;  // Määritetään sensorin pinni (analoginen pinni A4)
int ledPin = 9;      // Määritetään LEDin pinni (digitaalinen pinni 9)
int sensorValue = 0; // Alustetaan sensorin arvo
int val;             // Väliaikainen muuttuja ADC-lukemille
int ledState = LOW;  // Alustetaan LEDin tila alhaiseksi

void setup()
{
    Serial.begin(9600);        // Käynnistetään serial monitor
    pinMode(ledPin, OUTPUT);   // Asetetaan ledPin ulostuloksi
    digitalWrite(ledPin, LOW); // Asetetaan LED pois päältä
    ADC_init();                // Kutsutaan ADC_init funktiota ADC:n alustamiseksi
}

void loop()
{
    uint16_t sensorValue = ADC_read(sensorPin); // Luetaan sensorin arvo muuttujaan
    float voltage = sensorValue / 1023.0 * 5.0; // Lasketaan jännitte

    Serial.print("Voltage is: ");
    Serial.println(voltage);

    analogWrite(ledPin, sensorValue / 4); // Asetetaan LEDin jännite sensorin arvon mukaan
    delay(300);
}

void ADC_init()
{
    // rekisteriasetukset
    ADMUX |= (1 << REFS0) | (1 << MUX2); // Asetetaan referenssijännite ja ADC-muunnoskanava
    ADCSRA |= (1 << ADEN);               // Aktivoidaan ADC
    ADCSRB = 0x00;                       // Asetetaan ADCSRB rekisteri nolliksi
}

uint16_t ADC_read(uint8_t ch)
{
    // aloitetaan muunnos
    ADCSRA |= (1 << ADSC); // Käynnistetään ADC-muunnos

    while (ADCSRA & B00001000) // Odotetaan, että muunnos on valmis
    {
        ;
    }

    val = ADC;  // Luetaan ADC arvo
    return val; // Palautetaan ADC arvo
}
