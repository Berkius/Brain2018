void WriteSateliteAnglesFirst(){
  Serial.println("Entering WriteSateliteAnglesFirst");

  char receivedChars;  
  //Serial.flush(); //flush all previous received and transmitted data
  Serial.println("Waiting for user input for satelite coordinates (on form: )..");

  // Do Absolutely Nothing until something is received over the serial port
  while(!Serial.available()){}  //while(Serial.available() == 0x00)
  
  receivedChars = Serial.read(); //Read user input and trigger appropriate function

  // Remake received satelite coordinates to elevation angle
  Extract_Datas();
  
  Serial.println("Ending WriteSateliteAnglesFirst");
}

void WriteSateliteAngles(){
  Serial.println("Entering WriteSateliteAngles");

  char receivedChars;   
  
  if (Serial.available())
  {
    receivedChars = Serial.read(); //Read user input and trigger appropriate function

    // Remake received satelite coordinates to elevation angle
    Extract_Datas();
    Serial.println("New satelite coordinates recived");
  }

  Serial.println("Ending WriteSateliteAngles");
  
}
