#ifndef CADENCEGET_H
#define CADENCEGET_H
#include "variable.h"
void cadenceGetSpeed(){
    float last_time_cadence_intr = cad.getLastTimeInterruptMs();
    
    rpm_cadence = cad.getPulses() * 1000 * 60 /((SAMP_CAD_MS - (millis() - last_time_cadence_intr))*12);
    cad.reset();
    if (rpm_cadence > 500){
        rpm_cadence = 500;
    }

    #define CONST_FILTER_CADENCE 0.96
    rpm_cadence = CONST_FILTER_CADENCE*rpm_cadence + (1-CONST_FILTER_CADENCE)*last_rpm_cadence;

    accel_cadence = (rpm_cadence - last_rpm_cadence)*1000/SAMP_CAD_MS;
    last_rpm_cadence = rpm_cadence;
}

#endif