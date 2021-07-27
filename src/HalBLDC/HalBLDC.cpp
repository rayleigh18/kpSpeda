#include "HalBLDC.h"

HalBLDC *HalBLDC::sHal = 0;

HalBLDC::HalBLDC(int pinA, int pinB, int pinC, int ppr, Mode mode, bool isRev) : _pinA(pinA), _pinB(pinB), _pinC(pinC), _ppr(ppr)
{
    _pulses = 0;
    _mode = mode;
    if (isRev){
        _mult = 1.0;
    }
    else {
        _mult = -1.0;
    }
}

void HalBLDC::setup()
{
    pinMode(_pinA, INPUT_PULLUP);
    pinMode(_pinB, INPUT_PULLUP);
    if (_mode == MODE_3)
    {
        pinMode(_pinC, INPUT_PULLUP);
    }

    sHal = this;

    attachInterrupt(_pinA, HalBLDC::updateEncISR, CHANGE);
    attachInterrupt(_pinB, HalBLDC::updateEncISR, CHANGE);
    if (_mode == MODE_3)
    {
        attachInterrupt(_pinC, HalBLDC::updateEncISR, CHANGE);
    }

    bool stateA = digitalRead(_pinA);
    bool stateB = digitalRead(_pinB);
    if (_mode == MODE_3)
    {
        bool stateC = digitalRead(_pinC);
        curr_state = (stateA << 2) | (stateB | 1) | stateC;
    }
    else
    {
        curr_state = (stateA | 1) | stateB;
    }

    prev_state = curr_state;
}

void HalBLDC::reset()
{
    _pulses = 0;
}

int HalBLDC::getPulses()
{
    return _pulses*((int)_mult);
}

float HalBLDC::getRev()
{
    return (float)_pulses*_mult / _ppr;
}

void HalBLDC::updateEncISR()
{
    if (sHal != 0)
    {
        sHal->addPulseInInterrupt();
    }
}

void HalBLDC::addPulseInInterrupt(void)
{
    bool stateA = digitalRead(_pinA);
    bool stateB = digitalRead(_pinB);
    if (_mode == MODE_3)
    {
        bool stateC = digitalRead(_pinC);
        // jika pengen hemat, Y = !E!A + !F!B + !D!C, dimana DEF adalah last state
        curr_state = (stateA << 2) | (stateB | 1) | stateC;
    }
    else
    {
        curr_state = (stateA | 1) | stateB;
    }

    int change = 0;
    if (_mode == MODE_3)
    {
        if (
            (prev_state == 1 && curr_state == 5) ||
            (prev_state == 5 && curr_state == 4) ||
            (prev_state == 4 && curr_state == 6) ||
            (prev_state == 6 && curr_state == 2) ||
            (prev_state == 2 && curr_state == 3) ||
            (prev_state == 3 && curr_state == 1))
        {
            change = -1;
        }
        else if (
            (curr_state == 1 && prev_state == 5) ||
            (curr_state == 5 && prev_state == 4) ||
            (curr_state == 4 && prev_state == 6) ||
            (curr_state == 6 && prev_state == 2) ||
            (curr_state == 2 && prev_state == 3) ||
            (curr_state == 3 && prev_state == 1))
        {
            change = 1;
        }
    }
    else{
        if (((curr_state ^ prev_state) != INVALID) && (curr_state != prev_state)) {
            //2 bit state. Right hand bit of prev XOR left hand bit of current
            //gives 0 if clockwise rotation and 1 if counter clockwise rotation.
            change = (prev_state & PREV_MASK) ^ ((curr_state & CURR_MASK) >> 1);

            if (change == 0) {
                change = -1;
            }

            
        }
    }
    _pulses += change;
    prev_state = curr_state;
}