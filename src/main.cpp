#include <Arduino.h>
#define DEBUG
#define BLUETOOTH_INPUT
#include <BluetoothSerial.h>

#include "DriverBLDC/DriverBLDC.h"
#include "getDataFromSerial.h"
#include "HalBLDC/HalBLDC.h"
#include "CadenceSensor/CadenceSensor.h"
#include "cadenceGetSpeed.h"
#include "variable.h"
#include "control.h"



float rpm_last_motor = 0;
void setup()
{
  // put your setup codea here, to run once:
  Serial.begin(115200);
  SerialBT.begin("ESP32Test"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
  enc.setup();
  motor.setup();
  cad.setup();
}
void loop()
{
// put your main code here, to run repeatedly:
  if (millis() - time_sample_motor > 50)
  {
    #ifdef BLUETOOTH_INPUT
      recvWithStartEndMarkers(&SerialBT);
      parseData();
    #endif

    #define CONST_MULT 0.01    
      control();
      motor.inPWM(speed);
    time_sample_motor = millis();
  }

  if (millis() - time_sample_encoder > SAMP_ENC_MS)
  {
    rpm_motor  = enc.getRev() * 1000 * 60 / SAMP_ENC_MS;
    rpm_motor = 0.9*rpm_motor + 0.1 * rpm_last_motor;
    rpm_last_motor = rpm_motor;
    speed_bike = rpm_motor * R_RODA*60 /1000;
    enc.reset();
    time_sample_encoder = millis();
  }

  if (millis() - time_sample_cadence > SAMP_CAD_MS){
    cadenceGetSpeed();
    time_sample_cadence = millis();
  }


  #ifdef DEBUG
  if (millis() - time_sample_print > 100)
  {
    SerialBT.printf("%f %f %f %f %d\n", speed_bike, rpm_motor, speed, rpm_cadence, input);
    // Serial.printf("%d\n",enc.getPulses());
    time_sample_print = millis();
  }
  // Serial.println(analogRead(CADENCE));
  #endif
}