#ifndef CONTROL_H
#define CONTROL_H
#include "variable.h"
#define KP 0.0001
#define K_CAD 10
#define MAX_PWM 0.6

double fastPow(double a, double b) {
    union {
        double d;
        int x[2];
    } u = { a };
    u.x[1] = (int)(b * (u.x[1] - 1072632447) + 1072632447);
    u.x[0] = 0;
    return u.d;
}


float last_pwm_in = 0;
void control(){
    // if (bike_velo > 10  || bike_velo < 0){
    //   pwm_in = 0;
    // }
    // else{
    //   pwm_in = bike_velo * CONST_MULT + 0.0;
    // }

    // if (pwm_in > 0.4)
    // {
    //   pwm_in = 0.4;
    // }
    // else if (pwm_in < 0.0){
    //   pwm_in = 0.0;
    // }

    // /* Cara 2
    // */

    // float rpm_motor_dest = K_CAD * rpm_cadence;
    // // pwm_in = KP * (rpm_motor_dest + rpm_motor);

    // pwm_in = rpm_cadence*(1- fastPow(2.718281, -rpm_motor / 700)) / 100 + 0.03;

    // if (pwm_in < 0 || rpm_motor <= 1.0 || rpm_cadence <= 1){
    //   pwm_in = 0;
    // }
    // if (pwm_in > MAX_PWM) {
    //   pwm_in = MAX_PWM;
    // }

    /* Cara 3

    */
  
  // float max_pwm_input = (float)input/8;

  // pwm_in = max_pwm_input;
  // if (pwm_in < 0 || rpm_motor <= 1.0 || rpm_cadence <= 1){
  //   pwm_in = 0;
  // }
  // if (pwm_in > MAX_PWM) {
  //   pwm_in = MAX_PWM;
  // }

  /* Cara 4

  */

  // if (pwm_in < 0 || rpm_motor <= 1.0 || rpm_cadence <= 2.0){
  //   pwm_in = 0;
  // }
  // else if (rpm_motor > rpm_batas_1[mode]){
  //   float temp = (rpm_motor/(const_rpm));
  //   pwm_in = temp*temp + (50*rpm_batas_1[mode] + 9*rpm_batas_0)*(50*rpm_batas_1[mode] + 9*rpm_batas_0)/(22500*rpm_batas_0*rpm_batas_0);
  // }
  // else if (rpm_motor > rpm_batas_0){
  //   float temp = (rpm_motor/const_rpm);
  //   pwm_in = temp*temp + 0.06;
  // }
  // else if (accel_cadence > 50){
  //   pwm_in = const_pwm[mode] - (rpm_batas_0 - rpm_motor)*const_pwm[mode]/(rpm_batas_0);   // pwm start
  // }
  // else{
  //   pwm_in = 0;
  // }

  // if (pwm_in - last_pwm_in > max_delta_pwm){
  //   pwm_in = last_pwm_in + max_delta_pwm;
  // }

  /* Cara 5

  */
    /* Cara 4

  */
 float temp = -1*rpm_motor / d_const[mode];

  if (pwm_in < 0 || rpm_motor <= 1.0 || rpm_cadence <= 2.0){
    pwm_in = 0;
  }
  else if (accel_cadence > 10 && rpm_motor < rpm_batas_0){
    pwm_in = const_pwm[mode]*(1 - (rpm_batas_0 - rpm_motor)/(rpm_batas_0));   // pwm start
  }
  else if (rpm_motor > d_const[mode]*const_rpm_batas_1){
    float exp_atas = temp + d2_const[mode];
    pwm_in = (1 - fastPow(l_const[mode], exp_atas));   // pwm start
  }
  else if (rpm_motor > rpm_batas_0){
    pwm_in = i_const[mode]*temp*temp + 0.06;
  }
  else{
    pwm_in = 0;
  }
  

  if (pwm_in - last_pwm_in > max_delta_pwm){
    pwm_in = last_pwm_in + max_delta_pwm;
    last_pwm_in = pwm_in;
  }

  if (pwm_in > 1){
    pwm_in = 1;
  }
}

#endif