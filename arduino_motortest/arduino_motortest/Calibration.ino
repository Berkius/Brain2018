void Calibration(){
   
   if ((sensorValue_1==LOW) || (sensorValue_2=LOW)){ 
     Serial.println("inside if");
      //FOR THE UPPER MOTOR CONTROLLING THE ELEVATION
      while (digitalRead(sensor_Pin_1)==LOW){
        Pitch_Positive(setupSpeed);
        delay(DelayVar);
        }
        Serial.println("first while");
        Pitch_Brake();
        getCurrentAngles();              //Get current angle from the accelerometer 
        Serial.println(pitchdeg);   
        if (elevation_min!=pitchdeg){
          offset_el=abs(elevation_min-pitchdeg); //perhaps check function
          }  
        elevation_min=pitchdeg-offset_el;                 //minimum degree for the parabola
        Serial.println(offset_el);
        //Save the acc.meters value
        Pitch_Negative(setupSpeed);
        delay(100);
        delay(3000);
      while(digitalRead(sensor_Pin_1)==LOW){
        Pitch_Negative(setupSpeed);
        delay(DelayVar);
        Serial.println("inside next last while");
        } 
      if(digitalRead(sensor_Pin_1)==HIGH){
        Pitch_Brake();
        getCurrentAngles();            //Get current angle from the accelerometer
        elevation_max=pitchdeg-offset_el;
        Pitch_Positive(setupSpeed);
        delay(DelayVar);
        Serial.println("inside last while");
        } 
        elevation_center=(elevation_min+elevation_max)/2;   //Reletiv centered coordinate
        Serial.println("finish");
      /*while(!(pitchdeg<=(elevation_center+2) && pitchdeg>=(elevation_center-2))){         //As long as the angle is out of the interval keep on going
          getCurrentAngles();
          Pitch_Positive(setupSpeed);
          delay(DelayVar);
          Serial.println("before loop function");
          }
      Pitch_Brake();
      */
      /*   
      //FOR THE LOWER MOTOR CONTROLLING THE AZIMUTH
      while (sensorValue_2==LOW){
        Roll_Positiv(setupSpeed);
        delay(DelayVar);
        }
      while (sensroValue_1==HIGH){
        Roll_Breaffk();
        getCurrentAngles();              //Get current angle from the accelerometer
        if (rolldeg!=0){
          offset_az=rolldeg;
          }     
        azimuth_min=rolldeg-offset_az;                 //minimum degree for the parabola
        //Save the acc.meters value
        Roll_Negative(setupSpeed);
        delay(DelayVar);
        }
      while(sensorValue_2==LOW){
        Roll_Negative(setupSpeed);
        delay(DelayVar);
        } 
      while(sensorValue_2==HIGH){
        Roll_Brake();
        getCurrentAngles();            //Get current angle from the accelerometer
        azimuth_max=rolldeg-offset_az;
        Roll_Positive(setupSpeed);
        delay(DelayVar)
        } 
        azimuth_center=(azimuth_min+azimuth_max)/2;   //Reletiv centered coordinate
      while(!(rolldeg<=(azimuth_center+2) && rolldeg>=(azimuth_center-2))){         //As long as the angle is out of the interval keep on going
          getCurrentAngles();
          Roll_Positive(setupSpeed);
          delay(DelayVar);
          }   
       Roll_Brake(); 
       azimuth_min=azimuth_min+2;
       azimuth_max=azimuth_max-2;
       */
       elevation_min=elevation_min-2;
       elevation_max=elevation_max-2; 
   }
}

