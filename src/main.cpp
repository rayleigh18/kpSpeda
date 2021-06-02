#include <Arduino.h>

#include "DriverBLDC/DriverBLDC.h"

DriverBLDC motor(21,22,23, 0, 5000, 8);
void setup() {
  // put your setup code here, to run once:
  motor.setup();
  Serial.begin(9600);
}

float speed;
void loop() {
  // put your main code here, to run repeatedly:
  int value = analogRead(13);
  speed = 
  motor.inPWM(1);
  delay(10);
}