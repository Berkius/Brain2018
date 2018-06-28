void WriteSateliteAnglesFirst(){
  Serial.println("Entering WriteSateliteAnglesFirst");
 
  int i = 0;
   
  Serial.println("Waiting for user input for satelite coordinates (on form: AZ67.0 EL23.0)..");

  // Do Absolutely Nothing until something is received over the serial port
  while(!Serial.available()){}  //while(Serial.available() == 0x00)
  
  while (Serial.available())
  {    
    receivedChars[i] = Serial.read(); //Read user input and trigger appropriate function
    i++;    
  }
  receivedChars[i]='\0'
  if (i > 0){  
    Extract_Datas();   // Remake received satelite coordinates to elevation angle    
    }
  
  Serial.println("Ending WriteSateliteAnglesFirst");
}

void WriteSateliteAngles(){
  Serial.println("Entering WriteSateliteAngles");

  char receivedChars[20];   
  int i = 0;
  
  while (Serial.available())
  {    
    receivedChars[i] = Serial.read(); //Read user input and trigger appropriate function
    i++;    
  }
  receivedChars[i]='\0'
  if (i > 0){  
    Extract_Datas();   // Remake received satelite coordinates to elevation angle    
    }

  
  Serial.println("Ending WriteSateliteAngles");
  
}
