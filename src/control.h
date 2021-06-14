#ifndef CONTROL_H
#define CONTROL_H
#include "variable.h"
#define KP 0.0001
#define K_CAD 10
#define MAX_PWM 0.4
double fastPow(double a, double b) {
    union {
        double d;
        int x[2];
    } u = { a };
    u.x[1] = (int)(b * (u.x[1] - 1072632447) + 1072632447);
    u.x[0] = 0;
    return u.d;
}

void control(){
    // if (speed_bike > 10  || speed_bike < 0){
    //   speed = 0;
    // }
    // else{
    //   speed = speed_bike * CONST_MULT + 0.0;
    // }

    // if (speed > 0.4)
    // {
    //   speed = 0.4;
    // }
    // else if (speed < 0.0){
    //   speed = 0.0;
    // }

    /* Cara 2
    */

    float rpm_motor_dest = K_CAD * rpm_cadence;
    // speed = KP * (rpm_motor_dest + rpm_motor);

    speed = rpm_cadence*(1- fastPow(2.718281, -rpm_motor / 700)) / 100 + 0.03;

    if (speed < 0 || rpm_motor <= 1.0 || rpm_cadence <= 1){
      speed = 0;
    }
    if (speed > MAX_PWM) {
      speed = MAX_PWM;
    }
}

void controlDebug(){
    speed = (float)i / 50;
    //for debug motor using input from serial
    speed = (float)i/50;
    if (i == 1){
      motor.inPWM(speed);
    }
    else{
      motor.inPWM(0);
    }
}


#endif