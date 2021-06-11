#ifndef CONTROL_H
#define CONTROL_H
#include "variable.h"
#define KP 0.1
#define K_CAD 10
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
    speed = KP * (rpm_motor_dest - rpm_motor);

    if (speed < 0 || rpm_motor <= 20 || rpm_cadence <= 1){
      speed = 0;
    }
    if (speed > 0.2) {
      speed = 0.2;
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