// Variables for adc value, input and output voltages
int adc_value, input;
float output;

// Variable for tau, 100 ms
int t = 100;

void setup() {
  // D5 as output
  pinMode(5, OUTPUT);
  // A0 as input
  pinMode(A0, INPUT);
  // Start serial monitor
  Serial.begin(9600);
}

void loop() {
  // set input to 5V
  input = 5;
  digitalWrite(5, HIGH);
  // wait 1 tau
  delay(t);
  // read and convert the output
  adc_value = analogRead(A0);
  output = (adc_value * 5.0) / 1023.0;
  // print the values
  Serial.println("1 tau");
  Serial.print("Input: ");
  Serial.print(input);
  Serial.println("V");
  Serial.print("Output: ");
  Serial.print(output);
  Serial.println("V");

  // wait 1 more tau (2 tau now)
  delay(t);
  // read and convert the new output
  adc_value = analogRead(A0);
  output = (adc_value * 5.0) / 1023.0;

  Serial.println("2 tau");
  Serial.print("Input: ");
  Serial.print(input);
  Serial.println("V");
  Serial.print("Output: ");
  Serial.print(output);
  Serial.println("V");

  // wait 1 more tau (3 tau now)
  delay(t);
  // read and convert the output
  adc_value = analogRead(A0);
  output = (adc_value * 5.0) / 1023.0;

  Serial.println("3 tau");
  Serial.print("Input: ");
  Serial.print(input);
  Serial.println("V");
  Serial.print("Output: ");
  Serial.print(output);
  Serial.println("V");

  // set input to 0V
  input = 0;
  digitalWrite(5, LOW);
  // delay to empty the capacitor
  delay(500);
}
