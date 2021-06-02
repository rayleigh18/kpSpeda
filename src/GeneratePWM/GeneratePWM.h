#ifndef GENERATEPWM_H
#define GENERATEPWM_H
#include <Arduino.h>
class GeneratePWM{
    public :
    /** Create GeneratePWM interface
     * @param channel only 8, 10, 12, 15
     * @param freq
     * @param res
     */
    GeneratePWM(int pin, int channel, int freq, int res);

    /** Setup pwm
     * 
     */
    void setupPWM();

    /** Create PWM on channel 
     * @param dutyCycle range from 0 to 1
     * 
     */
    void createPWM(float dutyCycle);

private :
    int _pin;
    int _channel;
    int _freq;
    int _res;
    int max_duty_;
};


#endif
