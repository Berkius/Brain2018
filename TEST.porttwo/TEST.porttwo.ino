#include <SoftwareSerial.h> // used for serial communication through analouge pins and not the default ones

const byte rxpin = 10;
const byte txpin = 11;
SoftwareSerial mySerial(rxpin,txpin);   //RX, TX

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  


Serial.println("Goodnight moon");


mySerial.begin(9600);
mySerial.println("Hello world?");

}

void loop() {
   //put your main code here, to run repeatedly:

  if(mySerial.available())  {
    delay(500);
    Serial.write(mySerial.read());
  }
  if(Serial.available())  {
    delay(500);
    mySerial.write(Serial.read());
  }
  
  }
