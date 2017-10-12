/*
  Example for different sending methods
  
  https://github.com/sui77/rc-switch/
  
*/

#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();

void setup() {

  Serial.begin(9600);
  
  // Transmitter is connected to Arduino Pin #10  
  mySwitch.enableTransmit(10);
  mySwitch.setPulseLength(290);
}

int anz = 0;
void loop() {

  mySwitch.sendTriState("0F0F11F00010");
  Serial.println("Senden" + anz);
  anz ++;
  delay(1000);
}
