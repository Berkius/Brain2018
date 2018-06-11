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
  // initialize serial
  Serial.begin(57600);             // opens serial port, sets data rate to 9600 bps
  mySerial.begin(57600);     // second comport
  inputString.reserve(200);       // reserve 200 bytes for the inputString
}

void loop() {
  
  
  // put your main code here, to run repeatedly:
  //Serial.print("test1");
  serialEvent();      // Creates the array of information from

  //showNewData();      // Runs the show data function



  
  mySerial.listen();
  uint8_t char1 = mySerial.read();
  Serial.print(char1, HEX);
  /*
  char testbyte = mySerial.read();
  mySerial.end();
  delay(1000);
  Serial.print(testbyte);
  
  for (int i=0; i <= numChars; i++) {
    char testbyte = mySerial.read();
    Serial.print(testbyte);
  }

  Serial.print("end of session");
  */
   
  if (stringComplete == true) {
    
    Extract_Datas();
    stringComplete = false;
  }

  delay(500);
 

}



/*
-------------------------------------------------------------------------------------------------
SerialEvent occurs whenever a new data comes in the hardware serial RX. 
This routine is run between eash time loop() runs, so using delay inside 
loop can delay response. Multiple bytes of data may be available. 
--------------------------------------------------------------------------------------------
*/

void serialEvent() {

  mySerial.listen();      // listen to the second port
    
  static byte ndx = 0;  


     // LOOOK AT THISSSSSSS             
    char endMarker = '\r';


    
    char inChar;                        // the char that is coming in
    while (mySerial.available() > 0 && stringComplete == false) {
        inChar = mySerial.read();

        delay(500);
        
        if (inChar != endMarker) {
            receivedChars[ndx] = inChar;
            ndx++;
            if (ndx >= numChars) {
                ndx = numChars - 1;
            }
        }
        else {
            receivedChars[ndx] = '\0'; // terminate the string
            ndx = 0;
            stringComplete = true;
        }
    }
    mySerial.close();
}


/*
void showNewData() {
 if (stringComplete == true) {
 Serial.print("This just in ... ");
 Serial.println(receivedChars);
 stringComplete = false;
 }
}
*/

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
  Serial.print("String = " + inputString + "\r\n"); // prints the string, BUT WHAT IS THIS LAST PART??

  // take out the AZIMUT value
  String Azimut = inputString.substring(Az_0+1,Az_End);   // extract azimut angle from string. substring: starting index is included but not the ending one  
  Serial.print("Azimut = " + Azimut + "\r\n");            // prints the azimut

   //take out the ELEVATION angle
   String Elevation = inputString.substring(El_0+1);      // extract only the elevation angle. substring without end takes from starting index and the rest of the string
   El_0 = Elevation.indexOf('L');                         // gets the index of L
   El_End = Elevation.indexOf('.');                       // gets the point in the new elevation string

   String El = Elevation.substring(El_0+1,El_End);        // extract elevation angle from string. substring: starting index is included but not the ending one 
   Serial.print("Elevation = " + El + "\r\n");            // prints the elevation

   // making the system ready to take a new value
   inputString = "";                                       // clear the string
   stringComplete = false;                                //  make it start looking for a new string

   // converts strings to integer for motors later
  AZ_degree = Azimut.toInt();                           //makes int of the azimut
  EL_degree = El.toInt();                               //makes int of the elevation 

    
  
}












/*
 * 
 */

 /*
void serialEvent() {

-------------------------------------------------------------------------------------------------
SerialEvent occurs whenever a new data comes in the hardware serial RX. 
This routine is run between eash time loop() runs, so using delay inside 
loop can delay response. Multiple bytes of data may be available. 
--------------------------------------------------------------------------------------------

  char endMarker = '\n';
  Serial.listen();
  
  while (Serial.available() > 0)  {         // checks if there are any information available in the serial port
    Serial.println("test3");
    char inChar = Serial.read();  // declares a char and put the information from the serial port in it. DON`T KNOW WHAT (char) DOES??
    inputString += inChar;              // add the new char to the input string

          if (inChar == endMarker) {
                  stringComplete = true;
              }
          
  
 }
} */
