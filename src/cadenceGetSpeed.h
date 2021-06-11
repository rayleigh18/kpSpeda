#ifndef CADENCEGET_H
#define CADENCEGET_H
#include "variable.h"
void cadenceGetSpeed(){
    float last_time_cadence_intr = cad.getLastTimeInterruptMs();
    // if (last_time_cadence_intr < millis() -time_sample_cadence){
    //   rpm_cadence = 0;
    // }
    // else{
    rpm_cadence = cad.getPulses() * 1000 * 60 /((SAMP_CAD_MS - (millis() - last_time_cadence_intr))*12);
    // }
    #define CONST_FILTER_CADENCE 0.8
    rpm_cadence = CONST_FILTER_CADENCE*rpm_cadence + (1-CONST_FILTER_CADENCE)*last_rpm_cadence;
    cad.reset();
    last_rpm_cadence = rpm_cadence;
}

#endif