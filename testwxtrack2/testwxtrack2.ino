#include <SoftwareSerial.h> // used for serial communication through analouge pins and not the default ones

SoftwareSerial mySerial(10,11);   //RX, TX

String inputString = "";
boolean stringComplete = false;     // used to determine when the string is complete
const byte numChars = 30;           // just to have a maximum of chars
char receivedChars[numChars];       // array of chars to store the values in
int Az_0, Az_End;                   // Aximuth, refering to the index in the string that you get, the first interesting number and the last
int El_0, El_End;                   // Elevation, refering to the index in the string that you get, the first interesting number and the last
int AZ_degree, EL_degree;           // The values to be sent to the motors



void setup() {
  // put your setup code here, to run once:
   Serial.begin(9600);             // opens serial port, sets data rate to 9600 bps
   mySerial.begin(9600);     // second comport

}

void loop() {
  // put your main code here, to run repeatedly:

  //char char1 = mySerial.read();
  //delay(2000);
  //Serial.println(char1);
  serialEvent();

  if (stringComplete == true) {
    Extract_Datas();
    stringComplete = false;
  }

}

void serialEvent(){
  mySerial.listen();

  char endMarker= '\r'; // carrier return
  char inChar;
  uint8_t inHex;
  int i=0;
  
  while (mySerial.available() > 0 && stringComplete == false){
    inChar = mySerial.read();
    //inHex = mySerial.read();

    //if (inHex == 13){ // carrier return is the last caracter of the wxtrack string
    if (inChar == endMarker){
      stringComplete = true;
      receivedChars[i]='\0'; //terminates the string
      i=0;
    } else{
      receivedChars[i]=inChar;
      i++;
    }
  }
  delay(2000);
  //Serial.println(receivedChars);
  //stringComplete = false;
}

void Extract_Datas() {
/* Extract data and print the string when a newline arrives
-------------------------------------------------------------------------------------------------
THe string received has the following form 
AZ268.0 EL56.0
We extract only the numbers to send to the motors
--------------------------------------------------------------------------------------------
*/
  String str(receivedChars);
  //Serial.print(receivedChars);
  inputString = receivedChars;

  Az_0 = inputString.indexOf('Z');    // gets the index of the Z
  Az_End = inputString.indexOf('.');  // gets the index of the first point of the string, here the point in "268.0"
  El_0 = inputString.indexOf('L');    // gets the index of the L 

  // prints the string from the serial port
  Serial.println("-");
  Serial.println("String = " + inputString + "\r"); // prints the string, BUT WHAT IS THIS LAST PART??

  // take out the AZIMUT value
  String Azimut = inputString.substring(Az_0+1,Az_End);   // extract azimut angle from string. substring: starting index is included but not the ending one  
  Serial.println("Azimut = " + Azimut + "\r");            // prints the azimut

   //take out the ELEVATION angle
   String Elevation = inputString.substring(El_0+1);      // extract only the elevation angle. substring without end takes from starting index and the rest of the string
   El_0 = Elevation.indexOf('L');                         // gets the index of L
   El_End = Elevation.indexOf('.');                       // gets the point in the new elevation string

   String El = Elevation.substring(El_0+1,El_End);        // extract elevation angle from string. substring: starting index is included but not the ending one 
   Serial.println("Elevation = " + El + "\r");            // prints the elevation

   // making the system ready to take a new value
   inputString = "";                                       // clear the string
   //stringComplete = false;                                //  make it start looking for a new string

   // converts strings to integer for motors later
  AZ_degree = Azimut.toInt();                           //makes int of the azimut
  EL_degree = El.toInt();                               //makes int of the elevation 
}

