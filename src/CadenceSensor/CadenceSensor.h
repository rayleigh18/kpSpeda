#ifndef CADENCE_SENSOR_H
#define CADENCE_SENSOR_H
#include "Arduino.h"

class CadenceSensor{
public:
    CadenceSensor(int pin, int ppr);

    void setup(void);
    void reset(void);

    int getPulses(void);
    int getRev(void);
    unsigned long getLastTimeInterruptMs(void);
    void addPulseInInterrupt(void);


private:
    static CadenceSensor* sCad;
    static void updateCadISR();

    int _pin;
    unsigned long _last_time_in_ms;
    volatile int _pulses;
    int _ppr;
};

#endif