void Extract_Datas() {
/* Extract data from SerialEvent_tab and update the satelite angles AZ_degree & EL_degree (and print the string when a newline arrives)
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
