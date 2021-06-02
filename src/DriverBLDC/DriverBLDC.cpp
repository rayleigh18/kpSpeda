#include "DriverBLDC.h"

DriverBLDC::DriverBLDC(int dir, int brake, int pwm, int channel, int freq, int res):
    _dir(dir), _brake(brake), _pwmHandler(pwm, channel, freq, res){
    
}

void DriverBLDC::setup(){
    _pwmHandler.setupPWM();
    pinMode(_brake, OUTPUT);
    pinMode(_dir, OUTPUT);
    digitalWrite(_brake, 1);
    digitalWrite(_dir, 1);
}

void DriverBLDC::inPWM(float dutyCycle){
    digitalWrite(_brake, 1);
    bool isForward = 1;
    if (dutyCycle < 0){
        isForward = 0;
    }
    digitalWrite(_dir, isForward);
    _pwmHandler.createPWM(fabs(dutyCycle));
}

void DriverBLDC::forceBrake(){
    digitalWrite(_brake, 0);
    _pwmHandler.createPWM(0);
    isBrake = 1;
}
