#include <SoftwareSerial.h> // used for serial communication through analouge pins and not the default ones

SoftwareSerial mySerial(10,11);   //RX, TX

String inputString = "";            // String to save the input in 
boolean stringComplete = false;     // used to determine when the string is complete
const byte numChars = 25;           // just to have a maximum of chars (normally 23 + extra zero)
char receivedChars[numChars];       // array of chars to store the values in
int Az_0, Az_End;                   // Aximuth, refering to the index in the string that you get, the first interesting number and the last
int El_0, El_End;                   // Elevation, refering to the index in the string that you get, the first interesting number and the last
int AZ_degree, EL_degree;           // The values to be sent to the motors
boolean errorVariable = false;      // error vaiable



void setup() {
  // put your setup code here, to run once:
   Serial.begin(9600);             // opens serial port, sets data rate to 9600 bps
   mySerial.begin(9600);           // second comport

}

void loop() {
  // put your main code here, to run repeatedly:
  
  serialEvent();                // Goes into the serial event function and saves the data in an array 

// if everything is working and we get the right data and the right data length it will extract the AZIMUTH and ELEVATION 
  if (stringComplete == true  && errorVariable == false) {
    Extract_Datas();
    stringComplete = false;
  }
// if something is wrong with the the data length it will not go to the extract datas function and instead go here  
  else if (stringComplete == true && errorVariable == true) {
    stringComplete = false;
    errorVariable = false;
   }
  }

/*
-------------------------------------------------------------------------------------------------
SerialEvent occurs whenever a new data comes in the hardware serial RX. 
This routine is run between eash time loop() runs.
--------------------------------------------------------------------------------------------
*/

void serialEvent(){
  mySerial.listen();        //starts listening for data in the serialport mySerial

  char endMarker= '\r'; // carrier return
  char inChar;          // char for input 
  uint8_t inHex;        // HEX for input
  int i=0;              // index for looping array
  
  while (mySerial.available() > 0 && stringComplete == false){
    inChar = mySerial.read();     // read char from mySerial

    // if reading in HEX is neede
    //inHex = mySerial.read();
    //if (inHex == 13){ // carrier return is the last caracter of the wxtrack string
    
    if(i >= numChars) {       // to not exceed the index
        i = 0;     
        Serial.println("ERROR: data exceed length of array");
        errorVariable = true;
        stringComplete = true;
        }
        
     if (inChar == endMarker){
        stringComplete = true;    // to make it go out of the while loop because the string is done
        receivedChars[i]='\0';    //terminates the string correctly
        i = 0;                    // puts the index back to zero for next package of data
      } 
     else{
        receivedChars[i]=inChar;    // puts the new char in the next position in the array
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
AZ268.0 EL56.0 UP0 DN0.
We extract only the numbers to send to the motors
--------------------------------------------------------------------------------------------
*/



  if(receivedChars[0] != 'A') {
    Serial.println("ERROR: unknown data");
    return;         // goes back to main loop if it doesn´t find an A
  }
  
  String str(receivedChars);      // makes the array of input chars to a string  
  inputString = receivedChars;    // change name on the received chars string


  Az_0 = inputString.indexOf('Z');    // gets the index of the Z
  Az_End = inputString.indexOf('.');  // gets the index of the first point of the string, here the point in "268.0"
  El_0 = inputString.indexOf('L');    // gets the index of the L 

  // prints the string from the serial port as it was sent
  Serial.println("-");
  Serial.println("String = " + inputString + "\r"); // prints the string, end with carrier return 

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

