#include <Arduino.h>

#include "DriverBLDC/DriverBLDC.h"
#include "getDataFromSerial.h"
#include "HalBLDC/HalBLDC.h"
#include "CadenceSensor/CadenceSensor.h"
#define DEBUG
#define HALL_PIN_C 14
#define HALL_PIN_B 12
#define HALL_PIN_A 13
#define SAMP_ENC_MS 100
#define SAMP_CAD_MS 400

#define CADENCE 15

// 138 for sepeda, 60 for motor di meja
HalBLDC enc(HALL_PIN_A, HALL_PIN_B, HALL_PIN_C, 138);
DriverBLDC motor(22, 23, 21, 0, 5000, 8);
CadenceSensor cad(CADENCE, 6);

unsigned long time_sample_motor = 0;
#ifdef DEBUG
unsigned long time_sample_print = 0;
#endif
unsigned long time_sample_encoder = 0;
unsigned long time_sample_cadence = 0;

float rpm_motor = 0;
float rpm_cadence = 0;
float last_rpm_cadence = 0;
void printHello()
{
  Serial.println("Hallo");
}

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  enc.setup();
  motor.setup();
  cad.setup();
}
void loop()
{
  // put your main code here, to run repeatedly:
  if (millis() - time_sample_motor > 200)
  {
    recvWithStartEndMarkers();
    parseData();
    speed = (float)i / 50;
    if (speed > 0.2)
    {
      speed = 0.2;
    }
    else if (speed < 0.0){
      speed = 0.0;
    }
    motor.inPWM(speed);
    time_sample_motor = millis();
  }

  if (millis() - time_sample_encoder > SAMP_ENC_MS)
  {
    rpm_motor = enc.getRev() * 1000 * 60 / SAMP_ENC_MS;
    enc.reset();
    time_sample_encoder = millis();
  }

  if (millis() - time_sample_cadence > SAMP_CAD_MS){
    float last_time_cadence_intr = cad.getLastTimeInterruptMs();
    if (last_time_cadence_intr < time_sample_cadence){
      rpm_cadence = 0;
    }
    else{
      rpm_cadence = cad.getRev() * 1000 * 60 /(SAMP_CAD_MS - (millis() - last_time_cadence_intr));
    }
    #define CONST_FILTER_CADENCE 0.5
    rpm_cadence = CONST_FILTER_CADENCE*rpm_cadence + (1-CONST_FILTER_CADENCE)*last_rpm_cadence;
    last_rpm_cadence = rpm_cadence;
    time_sample_cadence = millis();
  }




  #ifdef DEBUG
  if (millis() - time_sample_print > 100)
  {
    Serial.printf("%f %f %f\n", enc.getRev(), rpm_motor, speed);
    // Serial.printf("%d\n",analogRead(CADENCE));
    time_sample_print = millis();
  }
  #endif
}