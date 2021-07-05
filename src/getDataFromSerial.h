#include <Arduino.h>
#include <BluetoothSerial.h>
#include "variable.h"
bool newData = false;
const byte numChars = 32;
#define K_RPM_C 1
#define K_RPM_P 2
#define K_RPM_V1 3
#define K_RPM_D 4
#define K_RPM_I 5
#define K_RPM_L 6
#define K_RPM_S 7
#define K_RPM_D2 8
#define K_RPM_M 9
#define K_NONE 0
char receivedChars[numChars];
char tempChars[numChars];

void parseData();
void changeVariable();
float pwm_in;
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
                    if (receivedChars[ndx-1] == 'p'){
                        type = K_RPM_P;
                    }
                    else if (receivedChars[ndx-1] == 'b'){
                        type = K_RPM_V1;
                    }
                    else if (receivedChars[ndx-1] == 'd'){
                        type = K_RPM_D;
                    }
                    else if (receivedChars[ndx-1] == 'i'){
                        type = K_RPM_I;
                    }
                    else if (receivedChars[ndx-1] == 'l'){
                        type = K_RPM_L;
                    }
                    else if (receivedChars[ndx-1] == 'e'){
                        type = K_RPM_D2;
                    }
                    else if (receivedChars[ndx -1] == 'm'){
                        type = K_RPM_M;
                    }
                    else{
                        type = K_NONE;
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
        const_pwm[mode] = input;
    }
    else if (type == K_RPM_V1){
        rpm_batas_1[mode] = input;
    }
    else if (type == K_RPM_D)
    {
        d_const[mode] = input;
    }
    else if (type == K_RPM_I)
    {
        i_const[mode] = input;
    }
    else if (type == K_RPM_L)
    {
        l_const[mode] = input;
    }
    else if (type == K_RPM_D2)
    {
        d2_const[mode] = input;
    }
    else if (type == K_RPM_M){
        int temps = (int)input;
        temps = (temps%3);
        mode = temps;
    }
}