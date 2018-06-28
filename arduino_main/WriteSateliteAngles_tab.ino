void WriteSateliteAnglesFirst(){
  Serial.println("Entering WriteSateliteAnglesFirst");

  char receivedChars;  
  //Serial.flush(); //flush all previous received and transmitted data
  Serial.println("Waiting for user input..");

  // TEST 
  //Serial.println(Serial.available());
  while (Serial.available())
  {    
    receivedChars[i] = Serial.read(); //Read user input and trigger appropriate function
    i++;    
  }
  if (i > 0){  
    receivedChars[i]='\0';
    Extract_Datas();   // Remake received satelite coordinates to elevation angle    
    }
  
  receivedChars = Serial.read(); //Read user input and trigger appropriate function

  // Remake received satelite coordinates to elevation angle
  //Extract_Datas();
  Serial.println("Ending WriteSateliteAnglesFirst");
}

void WriteSateliteAngles(){
  Serial.println("Entering WriteSateliteAngles");

  char receivedChars[]={};   
  
  while(Serial.available())
  {
    receivedChars = Serial.read(); //Read user input and trigger appropriate function

    // Remake received satelite coordinates to elevation angle
    Extract_Datas();
  }
<<<<<<< HEAD
=======
  receivedChars[i]='\0';
  if (i > 0){  
    Extract_Datas();   // Remake received satelite coordinates to elevation angle    
    }
>>>>>>> 58b85d52a7da326e73a0a5a17b5b2b6e5e1ef60e

  Serial.println("Ending WriteSateliteAngles");
  
}
