#ifndef HALBLDC_H
#define HALBLDC_H
#include "Arduino.h"



class HalBLDC {
public :
    HalBLDC(int pinA, int pinB, int pinC, int ppr);

    void setup(void);
    void reset(void);

    int getPulses(void);
    float getRev(void);
    void addPulseInInterrupt(void);
private:
    static HalBLDC* sHal;
    static void updateEncISR();
    int curr_state;
    int prev_state;
    int _pinA;
    int _pinB;
    int _pinC;
    volatile int _pulses;
    int _ppr;

};


#endif