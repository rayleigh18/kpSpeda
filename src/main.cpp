#include <Arduino.h>

#include "DriverBLDC/DriverBLDC.h"
#include "getDataFromSerial.h"
#include "HalBLDC/HalBLDC.h"

#define HALL_PIN_A 13
#define HALL_PIN_B 12
#define HALL_PIN_C 14

// 138 for sepeda, 60 for motor di meja
HalBLDC enc(HALL_PIN_A, HALL_PIN_B, HALL_PIN_C, 138);
DriverBLDC motor(21,22,23, 0, 5000, 8);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  enc.setup();
  motor.setup();
}
void loop() {
  // put your main code here, to run repeatedly:
  recvWithStartEndMarkers();
  parseData();
  speed = (float)i/50;
  
  motor.inPWM(speed);
  Serial.printf("%d %f %f\n",enc.getPulses(), enc.getRev(), speed);
  delay(10);
}