#ifndef DRIVERBLDC_H
#define DRIVERBLDC_H
#include <Arduino.h>
#include "GeneratePWM/GeneratePWM.h"

class DriverBLDC{
    public:
    DriverBLDC(int dir, int brake, int pwm, int channel, int freq, int res);

    void setup();

    
    bool isBrake; 

    void inPWM(float dutyCycle);

    void forceBrake();
    void releaseForceBrake();

    private:
    int _dir;
    int _brake;
    int _pwm;
    GeneratePWM _pwmHandler;
};

#endif