#ifndef VARIABLE_H
#define VARIABLE_H
#include "HalBLDC/HalBLDC.h"
#include "CadenceSensor/CadenceSensor.h"
#include "DriverBLDC/DriverBLDC.h"
#define HALL_PIN_C 14
#define HALL_PIN_B 12
#define HALL_PIN_A 13
#define SAMP_ENC_MS 100
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
BluetoothSerial SerialBT;

unsigned long time_sample_motor = 0;
#ifdef DEBUG
unsigned long time_sample_print = 0;
#endif
unsigned long time_sample_encoder = 0;
unsigned long time_sample_cadence = 0;

float rpm_motor = 0;
float rpm_last_motor = 0;
float accel_motor = 0;
float rpm_cadence = 0;
float last_rpm_cadence = 0;
float accel_cadence = 0;
float bike_velo = 0;


float rpm_batas_1[3] = {213, 373, 566}; // equation d_const/1.4
const float const_rpm_batas_1 = 0.7143;
float rpm_batas_0 = 50;

float const_pwm[3] = {0.1, 0.08, 0.05};

float max_delta_pwm = 0.05;
float input = 0;
int mode = 0;
float d_const[3]  = {350, 600, 900};
float i_const[3]  = {1.36, 1.36, 1.36};
float l_const[3]  = {51, 51, 51};
float d2_const[3] = {0.4, 0.4, 0.4};
#endif