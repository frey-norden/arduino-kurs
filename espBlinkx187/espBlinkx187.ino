int LED_BUILTIN = 2;
void setup() {
  pinMode (LED_BUILTIN, OUTPUT);

}

void loop() {
  // this loop does a triple
  digitalWrite(LED_BUILTIN, HIGH);
  delay(337);
  digitalWrite(LED_BUILTIN, LOW);
  delay(3337); // waiting period
  digitalWrite(LED_BUILTIN, HIGH);
  delay(337);
  digitalWrite(LED_BUILTIN, LOW);
  delay(337);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(337);
  digitalWrite(LED_BUILTIN, LOW);
  delay(337);
  

}
