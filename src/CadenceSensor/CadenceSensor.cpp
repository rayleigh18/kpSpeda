#include "CadenceSensor.h"

CadenceSensor* CadenceSensor::sCad = 0;

CadenceSensor::CadenceSensor(int pin, int ppr) : 
    _pin(pin), _ppr(ppr){
        _pulses = 0;
        _last_time_in_ms = 0;
    }

void CadenceSensor::setup(){
    pinMode(_pin, INPUT_PULLUP);
    sCad = this;

    attachInterrupt(_pin, CadenceSensor::updateCadISR, FALLING);
}

void CadenceSensor::reset(){
    _pulses = 0;
}

int CadenceSensor::getPulses(){
    return _pulses;
}

int CadenceSensor::getRev(){
    return (float)_pulses/_ppr;
}

void CadenceSensor::updateCadISR(){
    if (sCad !=0){
        sCad->addPulseInInterrupt();
    }
}

void CadenceSensor::addPulseInInterrupt(){
    _pulses++;
    _last_time_in_ms = millis();
}

unsigned long CadenceSensor::getLastTimeInterruptMs(){
    return _last_time_in_ms;
}