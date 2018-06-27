void WriteSateliteAnglesFirst(){
  Serial.print("Entering WriteSateliteAnglesFirst");

  char receivedChars;  
  Serial.println("Waiting for user input..");
  // Do Absolutely Nothing until something is received over the serial port
  while (!Serial.available()){}
  
  receivedChars = Serial.read(); //Read user input and trigger appropriate function

  // Remake received satelite coordinates to elevation angle
  Extract_Datas();
  Serial.print("Ending WriteSateliteAnglesFirst");
}

void WriteSateliteAngles(){
  Serial.print("Entering WriteSateliteAngles");

  char receivedChars;   
  
  while(Serial.available())
  {
    receivedChars = Serial.read(); //Read user input and trigger appropriate function

    // Remake received satelite coordinates to elevation angle
    Extract_Datas();
  }

  Serial.print("Ending WriteSateliteAngles");
  
}
