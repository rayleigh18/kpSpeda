#include "DriverBLDC.h"

DriverBLDC::DriverBLDC(int dir, int brake, int pwm, int channel, int freq, int res):
    _dir(dir), _brake(brake), _pwmHandler(pwm, channel, freq, res){
    
}

void DriverBLDC::setupMotor(){
    _pwmHandler.setupPWM();
    digitalWrite(_brake, 0);
    digitalWrite(_dir, 0);
}

void DriverBLDC::inPWM(float dutyCycle){
    digitalWrite(_brake, 0);
    int isForward = 1;
    if (dutyCycle < 0){
        isForward = 0;
    }
    digitalWrite(_dir, isForward);
    _pwmHandler.createPWM(dutyCycle);
}

void DriverBLDC::forceBrake(){
    digitalWrite(_brake, 1);
    _pwmHandler.createPWM(0);
    isBrake = 1;
}
