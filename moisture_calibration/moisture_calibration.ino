void setup() {
  analogReference(DEFAULT);
  Serial.begin(9600);
  analogRead(A0);
  delay(100);
}

void loop() {
  int val = analogRead(A0);
  Serial.println(val);
  delay(50);
}
