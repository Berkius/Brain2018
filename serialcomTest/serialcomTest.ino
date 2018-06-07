#include <SoftwareSerial.h> // used for serial communication through analouge pins and not the default ones

SoftwareSerial mySerial(11,10 );   //RX, TX

String inputString = "";
boolean stringComplete = false;   // used to determine when the string is complete

void setup() {
  // put your setup code here, to run once:
    // initialize serial
  Serial.begin(9600);             // opens serial port, sets data rate to 9600 bps
  // HÄÄÄÄÄÄÄÄÄÄÄÄR NEDAN ÄNDRAT
  mySerial.begin(9600);
  //mySerial.begin(9600); //HÅLL KOLL
  inputString.reserve(200);       // reserve 200 bytes for the inputString
}

void loop() {
  // put your main code here, to run repeatedly:

  serialEvent();

  // prints the string from the serial port
  //Serial.println("-");
  //Serial.print("String = " + inputString + "\r\n"); // prints the string, BUT WHAT IS THIS LAST PART??
}


const byte numChars = 20;
char receivedChars[numChars];

void serialEvent() {
    static byte ndx = 0;
    char endMarker = '\n';
    char rc;
    while (Serial.available() > 0 && stringComplete == false) {
        rc = Serial.read();

        if (rc != endMarker) {
            receivedChars[ndx] = rc;
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
/*
void serialEvent() {
/*
-------------------------------------------------------------------------------------------------
SerialEvent occurs whenever a new data comes in the hardware serial RX. 
This routine is run between eash time loop() runs, so using delay inside 
loop can delay response. Multiple bytes of data may be available. 
--------------------------------------------------------------------------------------------

// HÄR MED
  Serial.println("test1");
  mySerial.listen();
  Serial.println("test2");
  while (mySerial.available() > 0)  {         // checks if there are any information available in the serial port
  // INTE HÄR DVS DEN FÅR INGEN DATA 
  Serial.println("test3");
  char inChar = mySerial.read();  // declares a char and put the information from the serial port in it. DON`T KNOW WHAT (char) DOES??
  inputString += inChar;              // add the new char to the input string

  if(inChar == '{\r')  {              // if the incoming character is a newline, set a flag -> true so that the loop can do something = extract datas. WHAT IS '/r'???
    stringComplete = true; 
  }
  
 }
}*/
