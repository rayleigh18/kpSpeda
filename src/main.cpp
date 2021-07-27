  
#include <Arduino.h>

#define DEBUG
#define BLUETOOTH_INPUT
#include <BluetoothSerial.h>

#include "DriverBLDC/DriverBLDC.h"
#include "getDataFromSerial.h"
#include "HalBLDC/HalBLDC.h"
#include "CadenceSensor/CadenceSensor.h"
#include "cadenceGetSpeed.h"
#include "encGetSpeed.h"
#include "variable.h"
#include "control.h"

const char *ssid = "ESPAyam";
const char *password = "esppisang";

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
    #endif   
    control();
    motor.inPWM(pwm_in);
    time_sample_motor = millis();
  }

  if (millis() - time_sample_encoder > SAMP_ENC_MS)
  {
    encGetSpeed();
    time_sample_encoder = millis();
  }

  if (millis() - time_sample_cadence > SAMP_CAD_MS){
    cadenceGetSpeed();
    time_sample_cadence = millis();
  }

  #ifdef DEBUG
  if (millis() - time_sample_print > 700)
  {
    SerialBT.printf("%.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f %d\n", 
    rpm_motor, rpm_cadence, pwm_in,  const_pwm[mode], d_const[mode],
    i_const[mode], l_const[mode], d2_const[mode], mode);
    Serial.println("Check");
    // Serial.printf("%d\n",enc.getPulses());
    time_sample_print = millis();
  }
  #endif
}