#ifndef VARIABLE_H
#define VARIABLE_H
#include "HalBLDC/HalBLDC.h"
#include "CadenceSensor/CadenceSensor.h"
#include "DriverBLDC/DriverBLDC.h"
#define HALL_PIN_C 14
#define HALL_PIN_B 12
#define HALL_PIN_A 13
#define SAMP_ENC_MS 500
#define SAMP_CAD_MS 400
#define R_RODA 0.6

#define CADENCE 15

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

// 138 for sepeda, 60 for motor di meja
HalBLDC enc(HALL_PIN_A, HALL_PIN_B, HALL_PIN_C, 138);
DriverBLDC motor(22, 23, 21, 0, 5000, 8);
CadenceSensor cad(CADENCE,12);

unsigned long time_sample_motor = 0;
#ifdef DEBUG
unsigned long time_sample_print = 0;
#endif
unsigned long time_sample_encoder = 0;
unsigned long time_sample_cadence = 0;
BluetoothSerial SerialBT;


float rpm_motor = 0;
float rpm_cadence = 0;
float last_rpm_cadence = 0;
float speed_bike = 0;
float rpm_last_motor = 0;

int input = 0;
#endif