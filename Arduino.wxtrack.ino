#include <FlexiTimer2.h>  // lets you periodically run a function, by a configurable number of milliseconds
#include <SoftwareSerial.h> // used for serial communication through analouge pins and not the default ones

String inputString = "";          // the string where you save the input data from WXtrack(serial)
boolean stringComplete = false;   // used to determine when the string is complete
int Az_0, Az_End;                 // Aximuth, refering to the index in the string that you get, the first interesting number and the last
int El_0, El_End;                 // Elevation, refering to the index in the string that you get, the first interesting number and the last
int AZ_degree, El_degree;         // The values to be sent to the motors

// HERE HE HAS SOME OTHER ANGLES REGARDING THE ALIGNEMENT; HAVE TO BE CHECKED AFTER WE GOT MOTORS AND GYRO

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
