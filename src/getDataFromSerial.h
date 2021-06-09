#include <Arduino.h>
bool newData = false;
const byte numChars = 32;
char receivedChars[numChars];
char tempChars[numChars];

float speed;
int i = 0;

void recvWithStartEndMarkers() {
    static boolean recvInProgress = false;
    static byte ndx = 0;
    char endMarker = '\n';
    char rc;

    while (Serial.available() > 0 && newData == false) {
        rc = Serial.read();
        recvInProgress = true;

        if (recvInProgress == true) {
            if (rc != endMarker) {
                receivedChars[ndx] = rc;
                ndx++;
                if (ndx >= numChars) {
                    ndx = numChars - 1;
                }
            }
            else {
                receivedChars[ndx] = '\0'; // terminate the string
                recvInProgress = false;
                strcpy(tempChars, receivedChars);
                ndx = 0;
                newData = true;
            }
        }


    }
}

void parseData() {      // split the data into its parts
    i = atoi(tempChars);     // convert this part to an integer
    newData = false;

}