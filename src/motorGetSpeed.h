#include "variable.h"

void motorGetSpeed(){
    rpm_motor  = enc.getPulses() * 1000 * 60 / (SAMP_ENC_MS*138);
    enc.reset();
    // rpm_motor = 0.9*rpm_motor + 0.1 * rpm_last_motor;
    rpm_last_motor = rpm_motor;
    speed_bike = rpm_motor * R_RODA*60 /1000;
    
}