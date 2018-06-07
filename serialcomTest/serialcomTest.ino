#include <SoftwareSerial.h> // used for serial communication through analouge pins and not the default ones

SoftwareSerial mySerial(11,10 );   //RX, TX

String inputString = "";
boolean stringComplete = false;   // used to determine when the string is complete

void setup() {
  // put your setup code here, to run once:
  // initialize serial
  Serial.begin(9600);             // opens serial port, sets data rate to 9600 bps
  inputString.reserve(200);       // reserve 200 bytes for the inputString
}

void loop() {
  // put your main code here, to run repeatedly:

  serialEvent();      // Creates the array of information from

  showNewData();      // Runs the show data function
}




-------------------------------------------------------------------------------------------------
SerialEvent occurs whenever a new data comes in the hardware serial RX. 
This routine is run between eash time loop() runs, so using delay inside 
loop can delay response. Multiple bytes of data may be available. 
--------------------------------------------------------------------------------------------


void serialEvent() {
    const byte numChars = 20;           // just to have a maximum of chars
    char receivedChars[numChars];       // array of chars to store the values in
    static byte ndx = 0;                
    char endMarker = '\n';
    char inChar;                        // the char that is coming in
    while (Serial.available() > 0 && stringComplete == false) {
        inChar = Serial.read();

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
}

void showNewData() {
 if (stringComplete == true) {
 Serial.print("This just in ... ");
 Serial.println(receivedChars);
 stringComplete = false;
 }
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
