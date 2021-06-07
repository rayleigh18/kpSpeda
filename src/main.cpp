#include <Arduino.h>

#include "DriverBLDC/DriverBLDC.h"
#include "getDataFromSerial.h"
#include "HalBLDC/HalBLDC.h"

#define HALL_PIN_A 21
#define HALL_PIN_B 22
#define HALL_PIN_C 23

HalBLDC enc(HALL_PIN_A, HALL_PIN_B, HALL_PIN_C, 60);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  enc.setup();
}
void loop() {
  // put your main code here, to run repeatedly:
  Serial.printf("%d %f\n",enc.getPulses(), enc.getRev());
}
