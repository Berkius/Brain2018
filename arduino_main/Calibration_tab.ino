void Calibration(){
/* Calibrating the the end switches and the offset of the accelerometer 
 *
 *
 */
  // Define variables
  int elevation_center = 0;
  int azimuth_center = 0;
  int DelayVar=10;                  //Delay in milliseconds 
  
  Serial.println("Entering Calibration");
   
   if ((digitalRead(sensor_el)==LOW) || (digitalRead(sensor_az)==LOW)){      //If the end switches pins are low(not activated), so we do not start to drive in one direction when we are at an end swtich     
      
      // Drive elevation motor until activated the switch, log offset value and drive back until switch is unactivated

      // Drive elevation motor until hitting switch
      Serial.println("Drive elevation motor until hitting switch..");         
      while (digitalRead(sensor_el)==LOW){                //When the elevation switch is low 
        Pitch_Positive(fastSpeed);                       //drive positive direetion
        delay(DelayVar);                                //Was needed to know for how long to run
        getCurrentAngles();                               //gets the angles from accelerometer 
        //Serial.println("inside low loop ");
        }
      Pitch_Brake();                                      //When Sensor_el turns to High, brake
      Serial.println("Switch activated");                   

      // Log offset value                                          
      getCurrentAngles();                               //Get current angle from the accelerometer  
      if (elevation_min!=pitchdeg){                     //If they are not equal save the offset 
          offset_el=abs(elevation_min-pitchdeg);        
          }   
      Serial.print("offset_el: ");                //for testing purpose 
      Serial.println(offset_el);                  //for testing porpuse

      // Drive elevtation negative until switch is unactivated
      Serial.println("Drive elevtation negative until switch is unactivated..");
      while(digitalRead(sensor_el)==HIGH){  

        Pitch_Negative(fastSpeed);                  //Drive Backwards
        delay(DelayVar);
        //Serial.println("inside high loop");
      }
      Serial.println("Switch unactivated");

      /*
       * FOR EVELEVATION SWITCH NO 2 (WE PROB DEONT NEED THIS)
      while(digitalRead(sensor_el)==LOW){           //When low again dirve backwards  
        Pitch_Negative(fastSpeed);                 //Drive Backwards 
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
      */
        // WE WANT THIS DEPENDENT ON OFFSET?
        elevation_center=abs((elevation_min+elevation_max)/2);   //Get centered coordinate
        
        //THE CALIBRATION FOR THE ELEVATION IS NOW DONE AND THE NEXT WHILE LOOP WILL JUST PLACE THE ANTENNA IN THE CENTER.
      Serial.println("Centering the parabola");
      /*while(!((pitchdeg-offset_el)<=(elevation_center+2) && (pitchdeg-offset_el)>=(elevation_center-2))){         //As long as the angle is out of the interval keep on going
          getCurrentAngles();
          Pitch_Positive(fastSpeed);
          delay_s(DelayVar);
          }
      Pitch_Brake();*/
      Serial.println("Centering finished");
      
      Serial.println("Starting the Calibration for Azimuth angle")  
      //FOR THE LOWER MOTOR CONTROLLING THE AZIMUTH
      Serial.println("Waiting for the switch to be pushed");
       while (digitalRead(sensor_az)==LOW){
        Roll_Positive(setupSpeed);
        delay_s(DelayVar);                                //Was needed to know for how long to run, delay_s makes it possible to brake the drive in the middle of a command. 
        getCurrentAngles();                               //Gets the angles from accelerometer 
        }
        Roll_Brake();                                      //When Sensor_el turns to High, brake
        Serial.println("Switch activated");                   
  
        // Log offset value                                          
        getCurrentAngles();                               //Get current angle from the accelerometer  
        if (azimuth_min!=rolldeg){                     //If they are not equal save the offset 
            offset_az=abs(azimuth_min-rolldeg);        //Set the offset from zero, the offset_az needs to be used when checking the degree further in the program
            }   
        Serial.print("offset_az: ");                //for testing purpose 
        Serial.println(offset_az);                  //for testing porpuse
  
        // Drive elevtation negative until switch is unactivated
        Serial.println("Drive azimuthal motor negative until switch is unactivated..");
        while(digitalRead(sensor_az)==HIGH){  
  
          Roll_Negative(setupSpeed);                  //Drive Backwards
          delay_s(DelayVar);
          //Serial.println("inside high loop");
        }
        Serial.println("Switch unactivated");

      /*azimuth_center=(azimuth_min+azimuth_max)/2;   //Reletiv centered coordinate

      while(!(rolldeg<=(azimuth_center+2) && rolldeg>=(azimuth_center-2))){         //As long as the angle is out of the interval keep on going
          getCurrentAngles();
          Roll_Positive(fastSpeed);
          delay(DelayVar);
          }   
       Roll_Brake(); 
       azimuth_min=azimuth_min+2;
       azimuth_max=azimuth_max-2;
       elevation_min=elevation_min-2;
       elevation_max=elevation_max-2; 
    */   
   }

   Serial.println("Ending Calibration");
   
}

