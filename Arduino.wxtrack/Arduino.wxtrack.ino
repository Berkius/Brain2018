#include <FlexiTimer2.h>  // lets you periodically run a function, by a configurable number of milliseconds
#include <SoftwareSerial.h> // used for serial communication through analouge pins and not the default ones

SoftwareSerial mySerial(10,11);   //RX, TX

String inputString = "";          // the string where you save the input data from WXtrack(serial)
boolean stringComplete = false;   // used to determine when the string is complete
int Az_0, Az_End;                 // Aximuth, refering to the index in the string that you get, the first interesting number and the last
int El_0, El_End;                 // Elevation, refering to the index in the string that you get, the first interesting number and the last
int AZ_degree, EL_degree;         // The values to be sent to the motors

// HERE HE HAS SOME OTHER ANGLES REGARD ING THE ALIGNEMENT; HAVE TO BE CHECKED AFTER WE GOT MOTORS AND GYRO

void setup() {
  // put your setup code here, to run once:
  
  // HERE HE USES THE FLEXITIMER TO MAKE A LASER BLINK; I DON`T UNDERSTAND WHY OR IF IT DOES ANYTHING ELSE??


  // initialize serial
  Serial.begin(9600);             // opens serial port, sets data rate to 9600 bps
  // HÄÄÄÄÄÄÄÄÄÄÄÄR NEDAN ÄNDRAT
  mySerial.begin(9600);
  //mySerial.begin(9600); //HÅLL KOLL
  inputString.reserve(200);       // reserve 200 bytes for the inputString

  // HERE HE IS INITIALIZING THE MOTORS TOO
}

void loop() {
  // put your main code here, to run repeatedly:
  serialEvent();                //? new line available?????? HE HAS THIS INSIDE AND OUTSIDE THE LOOP, BUT THE EXAMPLE DO NOT...?
  
  // HIT KÖR DEN 
  if(stringComplete) {          // if yes=true then
    Extract_Datas();            // go to function extract data
    
// HERE YOU WILL HAVE ALL THE INSTRUCTIONS TO THE ENGINGE
    
  }
}

void serialEvent() {
/*
-------------------------------------------------------------------------------------------------
SerialEvent occurs whenever a new data comes in the hardware serial RX. 
This routine is run between eash time loop() runs, so using delay inside 
loop can delay response. Multiple bytes of data may be available. 
--------------------------------------------------------------------------------------------
*/
// HÄR MED
mySerial.listen();
while (mySerial.available())  {         // checks if there are any information available in the serial port
  // INTE HÄR DVS DEN FÅR INGEN DATA 
  char inChar = (char)mySerial.read();  // declares a char and put the information from the serial port in it. DON`T KNOW WHAT (char) DOES??
  inputString += inChar;              // add the new char to the input string

  if(inChar == '{\r')  {              // if the incoming character is a newline, set a flag -> true so that the loop can do something = extract datas. WHAT IS '/r'???
    stringComplete = true; 
  }
  
 }
}


void Extract_Datas() {
/* Extract data and print the string when a newline arrives
-------------------------------------------------------------------------------------------------
THe string received has the following form 
AZ268.0 EL56.0
We extract only the numbers to send to the motors
--------------------------------------------------------------------------------------------
*/
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

