void Calibration(){
   
   if ((sensorValue_1==LOW) || (sensorValue_2=LOW)){ 
       Serial.println("inside if");
      //FOR THE UPPER MOTOR CONTROLLING THE ELEVATION
      while (digitalRead(sensor_el)==LOW){
        Pitch_Positive(setupSpeed);
        delay(DelayVar);
        getCurrentAngles();
        delay(1000);
        }
        Serial.println("first while");
        Pitch_Brake();
        getCurrentAngles();              //Get current angle from the accelerometer 
        delay(1000);
        Serial.println(pitchdeg);   
        if (elevation_min!=pitchdeg){
          offset_el=abs(elevation_min-pitchdeg); //perhaps check function
          }  
        elevation_min=pitchdeg-offset_el; 
      while(digitalRead(sensor_el)==HIGH){  
        Serial.println("offset_el: ");
        Serial.println(offset_el);
        delay(1000);
        Pitch_Negative(pushSpeed);
        delay(DelayVar);
        Pitch_Brake();
      }
      while(digitalRead(sensor_el)==LOW){
        Pitch_Negative(setupSpeed);
        delay(DelayVar);
        getCurrentAngles();
        delay(1000);
        }
        Pitch_Brake();
        getCurrentAngles();            //Get current angle from the accelerometer
        elevation_max=pitchdeg-offset_el;   //The offset up and down is the same we assume 
                 
      while (digitalRead(sensor_el)==HIGH){
        Pitch_Positive(pushSpeed);
        delay(DelayVar);
        getCurrentAngles();
        delay(1000);
        Pitch_Brake();
        } 
        elevation_center=abs((elevation_min+elevation_max)/2);   //Reletiv centered coordinate
        Serial.println("finish");
      while(!(pitchdeg<=(elevation_center+2) && pitchdeg>=(elevation_center-2))){         //As long as the angle is out of the interval keep on going
          getCurrentAngles();
          delay(1000);
          Pitch_Positive(setupSpeed);
          delay(DelayVar);
          Serial.println("before loop function");
          Serial.println(elevation_center);
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

