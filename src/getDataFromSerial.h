#include <Arduino.h>
#include <BluetoothSerial.h>
#include "variable.h"
bool newData = false;
const byte numChars = 32;
#define K_RPM_C 1
#define K_RPM_P 2
#define K_NONE 0
char receivedChars[numChars];
char tempChars[numChars];

void parseData();
void changeVariable();
float speed;
int type = 0;
float i = 0;

void recvWithStartEndMarkers(BluetoothSerial *SerialBT) {
    static boolean recvInProgress = false;
    static byte ndx = 0;
    char endMarker = '\n';
    char rc;

    while ((*SerialBT).available() > 0 && newData == false) {
        rc = (*SerialBT).read();
        recvInProgress = true;

        if (recvInProgress == true) {
            if (rc != endMarker) {
                receivedChars[ndx] = rc;
                ndx++;
                if (ndx >= numChars) {
                    ndx = numChars - 1;
                }
                type = K_NONE;
            }
            else {
                if (ndx > 0){
                    if (receivedChars[ndx-1] == 'a'){
                        type = K_RPM_C;
                    }
                    else{
                        type = K_RPM_P;
                    }
                    receivedChars[ndx-1] = '\0'; // terminate the string
                    recvInProgress = false;
                    strcpy(tempChars, receivedChars);
                    ndx = 0;
                    newData = true;
                    parseData();
                    changeVariable();
                }
            }
        }
    }
}

void parseData() {      // split the data into its parts
    i = atof(tempChars);     // convert this part to an float
    input = i;
    newData = false;
}

void changeVariable(){
    if (type == K_RPM_P){
        const_pwm = input;
    }
    else if (type == K_RPM_C){
        const_rpm = input;
    }
}