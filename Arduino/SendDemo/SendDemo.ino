/*
  Example for different sending methods
  
  https://github.com/sui77/rc-switch/
  
*/
int led = D4; //GPIO5 = D1, GPIO0 = D3

void setup() {
}

void loop() {
  digitalWrite(led, HIGH);
  Serial.println("Aus");
  delay(1000);
  digitalWrite(led, LOW);
  Serial.println("An");
  delay(1000);
  
//  digitalWrite(led, HIGH);
//
//
//  digitalWrite(led, LOW);
}
