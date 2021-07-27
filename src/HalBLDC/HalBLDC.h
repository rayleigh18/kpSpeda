#ifndef HALBLDC_H
#define HALBLDC_H
#include "Arduino.h"

#define PREV_MASK 0x1 //Konstanta untuk mengetahui previous direction
#define CURR_MASK 0x2 //Konstanta untuk mengetahui current direction
#define INVALID   0x3 //XORing two states where both bits have changed.



class HalBLDC {
public :
    typedef enum Mode{
        MODE_2,
        MODE_3
    }Mode;

    HalBLDC(int pinA, int pinB, int pinC, int ppr, Mode mode = MODE_3, bool isRev = false);

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
    Mode _mode;
    float _mult;

};


#endif