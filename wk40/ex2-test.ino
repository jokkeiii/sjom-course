#define ntc_pin A0
#define vd_power_pin 2
#define nominal_resistance 100000
#define nominal_temperature 25
#define samplingrate 5
#define beta 3950
#define Rref 100000

long samples = 0; // Changed from int to long

void setup(void)
{
    pinMode(vd_power_pin, OUTPUT);
    Serial.begin(9600);
}

void loop(void)
{
    uint8_t i;
    float average;
    samples = 0;

    digitalWrite(vd_power_pin, HIGH);

    for (i = 0; i < samplingrate; i++)
    {
        samples += analogRead(ntc_pin);
        delay(10);
    }

    digitalWrite(vd_power_pin, LOW);

    average = (float)samples / samplingrate; // Cast to float for more accurate division

    Serial.println("\n \n");
    Serial.print("ADC readings ");
    Serial.println(average);

    if (average != 0)
    {
        // Check to avoid division by zero
        average = 1023.0 / average - 1;
        average = Rref / average;

        Serial.print("Thermistor resistance ");
        Serial.println(average);

        // Steinhart-Hart
        float temperature;
        temperature = average / nominal_resistance;
        temperature = log(temperature);
        temperature /= beta;
        temperature += 1.0 / (nominal_temperature + 273.15);
        temperature = 1.0 / temperature;
        temperature -= 273.15;

        Serial.print("Temperature ");
        Serial.print(temperature);
        Serial.println(" *C");
    }
    else
    {
        Serial.println("Reading is zero, can't calculate temperature");
    }

    delay(2000);
}
