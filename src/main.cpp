#include <Arduino.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <ESPmDNS.h>
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
  while (WiFi.waitForConnectResult() == !WL_CONNECTED){
    Serial.println("FAILED C");
    delay(5000);
    ESP.restart();
  }
  enc.setup();
  motor.setup();
  cad.setup();
  ArduinoOTA
    .onStart([]() {
      String type;
      if (ArduinoOTA.getCommand() == U_FLASH)
        type = "sketch";
      else // U_SPIFFS
        type = "filesystem";

      // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
      Serial.println("Start updating " + type);
    })
    .onEnd([]() {
      Serial.println("\nEnd");
    })
    .onProgress([](unsigned int progress, unsigned int total) {
      Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
    })
    .onError([](ota_error_t error) {
      Serial.printf("Error[%u]: ", error);
      if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
      else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
      else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
      else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
      else if (error == OTA_END_ERROR) Serial.println("End Failed");
    });
    ArduinoOTA.begin();
    Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}
void loop()
{
  ArduinoOTA.handle();
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