#ifndef ENCGETSPEED_H
#define ENCGETSPEED_H

#include "variable.h"

void encGetSpeed(){
    rpm_motor  = enc.getRev() * 1000 * 60 / SAMP_ENC_MS;
    enc.reset();
    rpm_motor = 0.9*rpm_motor + 0.1 * rpm_last_motor;
    accel_motor = (rpm_motor - rpm_last_motor)*1000/SAMP_ENC_MS;
    rpm_last_motor = rpm_motor;
    bike_velo = rpm_motor * R_RODA*60 /1000;
}

#endif