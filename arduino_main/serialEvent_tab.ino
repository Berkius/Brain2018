/*
-------------------------------------------------------------------------------------------------
SerialEvent occurs whenever a new data comes in the hardware serial RX. 
This routine is run between eash time loop() runs.
--------------------------------------------------------------------------------------------
*/
void serialEvent(){
  /*
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
    */

    receivedChars = "AZ120.0 EL60.0 UPO \0";
  
  //delay(2000);
  //Serial.println(receivedChars);
  //stringComplete = false;
}
