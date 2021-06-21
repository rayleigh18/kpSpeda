#include <Arduino.h>
#define DEBUG
// #define BLUETOOTH_INPUT
#include <BluetoothSerial.h>

#include "DriverBLDC/DriverBLDC.h"
#include "getDataFromSerial.h"
#include "HalBLDC/HalBLDC.h"
#include "CadenceSensor/CadenceSensor.h"
#include "cadenceGetSpeed.h"
#include "motorGetSpeed.h"
#include "variable.h"
#include "control.h"

#include "SPIFFS.h"




void setup()
{
  // put your setup codea here, to run once:
  Serial.begin(115200);
  SerialBT.begin("ESP32Test"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
  enc.setup();
  motor.setup();
  cad.setup();
  if (!SPIFFS.begin(true)){
    Serial.println("An Error has Occured while Mounting SPIFFS");
    return;
  }

  File file = SPIFFS.open("/text.txt", FILE_WRITE);
  if (!file){
    Serial.println("There was an error opening the file for writing");
    return;
  }
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

    controlDebug();
    motor.inPWM(speed);


    time_sample_motor = millis();
  }

  if (millis() - time_sample_encoder > SAMP_ENC_MS)
  {
    motorGetSpeed();
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