
// This code is sparse in comments; check the document "Code_Explanations" or of a similar name for an explanation.
//----------------------------------------------------------------Part 1
int sensorReadings[13] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int variablePlaceWriteTo = 0;
int readFailure = 0;
int i = 0;
int highestTemp = 0;
boolean commFailure = false;
#include <Wire.h>

void setup() {
  Wire.begin();
  Serial.begin(9600);
  //delay(100);
}
//----------------------------------------------------------------Part 2
void loop() {
  resetVars(); // defined below
  for (i = 72; i < 78; i++) {
    Wire.flush();
    Wire.requestFrom(i, 2); // check how many bytes ro recieve
    while(Wire.available()) {
      sensorReadings[variablePlaceWriteTo] = Wire.read();
      variablePlaceWriteTo++;
    }
  }
  //--------------------------------------------------------------Part 3
  if (variablePlaceWriteTo != 12) {
    readFailure++;
    commFailure = true;
  }
  else {
    readFailure = 0;
  }
  // -------------------------------------------------------------Part 4
  if (!commFailure) {
    for (i = 0; i < 11; i = i+2) {
      sensorReadings[i] = sensorReadings[i]*4;
      if (sensorReadings[i+1] >= 128) {
        sensorReadings[i] = sensorReadings[i]+2;
        sensorReadings[i+1] = sensorReadings[i+1] - 128;  // extracts final two bits
      }
      if (sensorReadings[i+1] >= 64) {
        sensorReadings[i] = sensorReadings[i]+1;
      }
    }
    //------------------------------------------------------------Part 5
    highestTemp = max(sensorReadings[0], sensorReadings[2]);
    highestTemp = max(highestTemp, sensorReadings[4]);
    highestTemp = max(highestTemp, sensorReadings[6]);
    highestTemp = max(highestTemp, sensorReadings[8]);
    highestTemp = max(highestTemp, sensorReadings[10]);
    Serial.write(highestTemp);
    delay(200);                               // check for best delay time
  }
  else if (readFailure > 5) {  // if reading the sensors has failed 5 times in a row
    Serial.write(255);
    delay(200);
  }
}
//----------------------------------------------------------------End Of Loop     

void resetVars() {     // reset variables function
  commFailure = false;
  variablePlaceWriteTo = 0;
  for (i = 0; i < 12; i++) {
    sensorReadings[i] = 0;
  }
}
      
