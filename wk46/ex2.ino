int adc_value, input;
float output;

void setup() {
  pinMode(5, OUTPUT);
  pinMode(A0, INPUT);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(5, HIGH);
  delay(500);
  adc_value = analogRead(A0);
  output = (adc_value * 5.0) / 1023.0;
  input = 5;
  Serial.print("Input:");
  Serial.print(input);
  Serial.print(",");
  Serial.print("Output:");
  Serial.println(output);

  digitalWrite(5, LOW);
  delay(500);
  adc_value = analogRead(A0);
  output = (adc_value * 5.0) / 1023.0;
  input = 0;
  Serial.print("Input:");
  Serial.print(input);
  Serial.print(",");
  Serial.print("Output:");
  Serial.println(output);
}
