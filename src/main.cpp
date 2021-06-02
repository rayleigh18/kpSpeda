#include <Arduino.h>
#include "GeneratePWM/GeneratePWM.h"
#define POTENS 35
GeneratePWM motor(23, 0, 10000, 8);
void setup() {
  // put your setup code here, to run once:
  pinMode(POTENS, INPUT);
  motor.setupPWM();
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int value = analogRead(POTENS);
  float pwm = (float)value/4095;
  Serial.print(pwm);
  Serial.print(" ");
  motor.createPWM(0.5);
  delay(100);
}