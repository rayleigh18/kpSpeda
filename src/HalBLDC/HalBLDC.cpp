#include "HalBLDC.h"

HalBLDC* HalBLDC::sHal = 0;

HalBLDC::HalBLDC(int pinA, int pinB, int pinC, int ppr) :
    _pinA(pinA), _pinB(pinB), _pinC(pinC), _ppr(ppr)
{
    _pulses = 0;
}

void HalBLDC::setup(){
    pinMode(_pinA, INPUT_PULLUP);
    pinMode(_pinB, INPUT_PULLUP);
    pinMode(_pinC, INPUT_PULLUP);

    sHal = this;

    attachInterrupt(_pinA, HalBLDC::updateEncISR, CHANGE);
    attachInterrupt(_pinB, HalBLDC::updateEncISR, CHANGE);
    attachInterrupt(_pinC, HalBLDC::updateEncISR, CHANGE);
    bool stateA = digitalRead(_pinA);
    bool stateB = digitalRead(_pinB);
    bool stateC = digitalRead(_pinC);

    curr_state = (stateA << 2) | (stateB << 1) | stateC;
    prev_state = curr_state;
}

void HalBLDC::reset(){
    _pulses = 0;
}

int HalBLDC::getPulses(){
    return _pulses;
}

float HalBLDC::getRev(){
    return (float)_pulses/_ppr;
}

void HalBLDC::updateEncISR(){
    if (sHal != 0){
        sHal->addPulseInInterrupt();
    }
}

void HalBLDC::addPulseInInterrupt(void){
    bool stateA = digitalRead(_pinA);
    bool stateB = digitalRead(_pinB);
    bool stateC = digitalRead(_pinC);


    // jika pengen hemat, Y = !E!A + !F!B + !D!C, dimana DEF adalah last state
    curr_state = (stateA << 2) | (stateB << 1) | stateC;

    int change = 0;
    if (
        (prev_state == 1 && curr_state == 5) ||
        (prev_state == 5 && curr_state == 4) ||
        (prev_state == 4 && curr_state == 6) ||
        (prev_state == 6 && curr_state == 2) ||
        (prev_state == 2 && curr_state == 3) ||
        (prev_state == 3 && curr_state == 1)
        ){
            change = -1;
        }
    else if (
        (curr_state == 1 && prev_state == 5) ||
        (curr_state == 5 && prev_state == 4) ||
        (curr_state == 4 && prev_state == 6) ||
        (curr_state == 6 && prev_state == 2) ||
        (curr_state == 2 && prev_state == 3) ||
        (curr_state == 3 && prev_state == 1)
        ){
            change = 1;
        }
    _pulses += change;
    prev_state = curr_state;

}