//Calibrating the the end switches and the offset of the accelerometer 

void Calibration(){
   
   if ((sensorValue_1==LOW) || (sensorValue_2=LOW)){      //If the end switches pins are low(not activated)    
       Serial.println("inside if");                       //For testing in serial monitor
      //FOR THE UPPER MOTOR CONTROLLING THE ELEVATION     
      while (digitalRead(sensor_el)==LOW){                //When the elevation switch is low 
        Pitch_Positive(setupSpeed);                       //drive positive direetion
        delay(DelayVar);                                  //Was needed to know for how long to run
        getCurrentAngles();                               //gets the angles from accelerometer 
        }
      Serial.println("first while");                    //for testing
      Pitch_Brake();                                    //When Sensor_el turns to High, brake
      getCurrentAngles();                               //Get current angle from the accelerometer 
      Serial.println(pitchdeg);   
      if (elevation_min!=pitchdeg){                     //If they are not equal save the offset 
          offset_el=abs(elevation_min-pitchdeg);        
          }   
      while(digitalRead(sensor_el)==HIGH){  
        Serial.println("offset_el: ");              //for testing purpose 
        Serial.println(offset_el);                  //for testing porpuse
        Pitch_Negative(pushSpeed);                  //Drive Backwords
        delay(DelayVar);
        Pitch_Brake();                              //Dosen't konw if we need this it was an original thought but can be removed 
      }
      while(digitalRead(sensor_el)==LOW){           //When low again dirve backwards  
        Pitch_Negative(setupSpeed);                 //Drive Backwards 
        delay(DelayVar);                    
        getCurrentAngles();                         //Get angles from accelerometer  
        }
      Pitch_Brake();
      getCurrentAngles();                           //Get current angle from the accelerometer 
      while (digitalRead(sensor_el)==HIGH){         //When switch is set high from the other direction  
        Pitch_Positive(pushSpeed);                  // drive forward
        delay(DelayVar);            
        getCurrentAngles();                         //Get angles from accelerometer
        Pitch_Brake();                              //Dosen't konw if we need this it was an original thought but can be removed
        } 
        elevation_center=abs((elevation_min+elevation_max)/2);   //Get centered coordinate
        //THE CALIBRATION IS NOW DONE AND THE NEXT WHILE LOOP WILL JUST PLACE THE ANTENNA IN THE CENTER.
      while(!((pitchdeg-offset_el)<=(elevation_center+2) && (pitchdeg-offset_el)>=(elevation_center-2))){         //As long as the angle is out of the interval keep on going
          getCurrentAngles();
          Pitch_Positive(setupSpeed);
          delay(DelayVar);
          Serial.println("before loop function");       //For testing in serial monitor
          Serial.println(elevation_center);             //For testing in serial monitor
          }
      Pitch_Brake();
      
      /*  
      //FOR THE LOWER MOTOR CONTROLLING THE AZIMUTH
     
      while (sensorValue_2==LOW){
        Roll_Negative(setupSpeed);
        delay(DelayVar);
        getCurrentAngles();
        delay(1000);
        Serial.println("First While");
        }
      while (sensorValue_1==HIGH){
        Roll_Brake();
        getCurrentAngles();              //Get current angle from the accelerometer
        delay(1000);
        if (rolldeg!=0){
          offset_az=rolldeg;
          }     
        azimuth_min=rolldeg-offset_az;                 //minimum degree for the parabola
        //Save the acc.meters value
        Roll_Positive(setupSpeed);
        delay(DelayVar);
        Serial.println("second while");
        Serial.println("Print Offset");
        Serial.println(offset_az);
        }
      while(sensorValue_2==LOW){
        Roll_Positive(setupSpeed);
        delay(DelayVar);
        getCurrentAngles();
        delay(1000);
        Serial.println("third while");
        } 
      while(sensorValue_2==HIGH){
        Roll_Brake();
        getCurrentAngles();            //Get current angle from the accelerometer
        delay(1000);
        azimuth_max=rolldeg-offset_az;
        Roll_Positive(setupSpeed);
        delay(DelayVar);
        Serial.println("Last while");
        } 
        /*azimuth_center=(azimuth_min+azimuth_max)/2;   //Reletiv centered coordinate
      while(!(rolldeg<=(azimuth_center+2) && rolldeg>=(azimuth_center-2))){         //As long as the angle is out of the interval keep on going
          getCurrentAngles();
          Roll_Positive(setupSpeed);
          delay(DelayVar);
          }   
       Roll_Brake(); 
       azimuth_min=azimuth_min+2;
       azimuth_max=azimuth_max-2;
       elevation_min=elevation_min-2;
       elevation_max=elevation_max-2; 
    */   
   }
   
}

