void WriteSateliteAngles(){

  char receivedChars;   
  
  while(Serial.available())
  {
    receivedChars = Serial.read(); //Read user input and trigger appropriate function

    // Remake received satelite coordinates to elevation angle
    Extract_Datas();
  }
  
}
