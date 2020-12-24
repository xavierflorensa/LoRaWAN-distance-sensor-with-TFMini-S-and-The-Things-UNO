 /*
  * @File  : DFRobot_TFmini_test.ino
  * @Brief : This example use TFmini to measure distance
  *         With initialization completed, we can get distance value and signal strength
  * @Copyright   [DFRobot](http://www.dfrobot.com), 2016
  *             GNU Lesser General Public License
  *
  * @version  V1.0
  * @date  2018-1-10
  */
#include <DFRobot_TFmini.h>
SoftwareSerial mySerial(8, 7); // RX, TX
DFRobot_TFmini  TFmini;
uint16_t distance,strength; 

#include <TheThingsNetwork.h>
const char *appEui = "your_appEui";
const char *appKey = "your_appKey";
#define loraSerial Serial1
#define debugSerial Serial
#define freqPlan TTN_FP_EU868
TheThingsNetwork ttn(loraSerial, debugSerial, freqPlan);
void setup() {
  loraSerial.begin(57600);
  debugSerial.begin(9600);
  TFmini.begin(mySerial);
  // Wait a maximum of 10s for Serial Monitor
  while (!debugSerial && millis() < 10000);
  debugSerial.println("-- STATUS");
  ttn.showStatus();
  debugSerial.println("-- JOIN");
  ttn.join(appEui, appKey);
}
void loop() {
   if(TFmini.measure()){                      //Measure Distance and get signal strength
        distance = TFmini.getDistance();       //Get distance data
        strength = TFmini.getStrength();       //Get signal strength data
        Serial.print("Distance = ");
        Serial.print(distance);
        Serial.println("mm");
        Serial.print("Strength = ");
        Serial.println(strength);
    }
  debugSerial.println("-- LOOP");
  byte payload[2];
  payload[0]=highByte(distance);
  payload[1]=lowByte(distance);
  ttn.sendBytes(payload, sizeof(payload));
  delay(10000);
}
