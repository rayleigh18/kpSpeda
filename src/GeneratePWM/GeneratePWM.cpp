#include "GeneratePWM.h"

GeneratePWM::GeneratePWM(int pin, int channel, int freq, int res):
    _pin(pin), _channel(channel), _freq(freq), _res(res){
    if (_res == 8){
        max_duty_ = 255;
    }
    else if (_res == 10){
        max_duty_ = 1023;
    }
    else if (_res == 12){
        max_duty_ = 4095;
    }
    else if (_res == 15){
        max_duty_ = 4096*4096*2 - 1;
    }
    else {
        max_duty_ = 255;
    }
}

void GeneratePWM::setupPWM(){
    ledcSetup(_channel, _freq, _res);
    ledcAttachPin(_pin, _channel);
}

void GeneratePWM::createPWM(float dutyCycle){
    int pwm = (dutyCycle*max_duty_);
    if (pwm > max_duty_){
        pwm = max_duty_;
    }
    Serial.println(pwm);
    ledcWrite(_channel, pwm);
}