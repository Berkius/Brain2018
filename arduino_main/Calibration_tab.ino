void Calibration(){
/* Calibrating the IMU (accelerometer & gyroscope) with the end switches
 *
 * Creating offeset fr the accelerometer and setting the roll angle 
 * 
 * Accelerometer caliration: Drive pitch motor until activated the switch, log offset value and drive back until switch is unactivated
 * 
 * Gyroscope caliration: Drive roll motor until activated the switch, log roll angle and drive back until switch is unactivated
 *
 * Date: 2018-06-29
 */

  // Define variables
  int elevation_center = 0;
  int azimuth_center = 0;
  int DelayVar=100;
  
  Serial.println(F("Entering Calibration"));

 // Starting the calibration if both sensor are unactivated    
 if ((digitalRead(sensor_el)==LOW) || (digitalRead(sensor_az)==LOW)){      

    // ##################################################
    // Calibration of accelerometer
    
    // Drive pitch motor until hitting switch
    Serial.println(F("Drive pitch motor until hitting switch.."));         
    while (digitalRead(sensor_el)==LOW){                  // When the pitch switch is low 
      Pitch_Positive(fastSpeed);                          // Drive positive direetion
      delay(DelayVar);                                    // Was needed to know for how long to run
      getCurrentPitch();                                  // Gets the angles from accelerometer 
    }
      
    Pitch_Brake();                                        // When Sensor_el turns to High, brake
    Serial.println(F("Switch activated"));                   

    // Log offset value                                          
    getCurrentPitch();                                    // Get current angle from the accelerometer  
    if (elevation_min!=pitchdeg){                         // If they are not equal save the offset 
        offset_el=abs(elevation_min-pitchdeg);        
        }   
    //Serial.print(F("offset_el: "));                          // For testing purpose 
    //Serial.println(F(offset_el));                            // For testing porpuse

    // Drive elevtation negative until switch is unactivated
    Serial.println("Drive elevtation negative until switch is unactivated..");
    while(digitalRead(sensor_el)==HIGH){  

<<<<<<< HEAD
      // Drive elevation motor until hitting switch
      Serial.println("Drive elevation motor until hitting switch..");         
      while (digitalRead(sensor_el)==LOW){                //When the elevation switch is low 
        Pitch_Positive(fastSpeed);                       //drive positive direetion
        delay(DelayVar);                                //Was needed to know for how long to run
        getCurrentPitch();                               //gets the angles from accelerometer 
        //Serial.println("inside low loop ");
        }
      Pitch_Brake();                                      //When Sensor_el turns to High, brake
      Serial.println("Switch activated");                   

      // Log offset value                                          
      getCurrentPitch();                               //Get current angle from the accelerometer  
      if (elevation_min!=pitchdeg){                     //If they are not equal save the offset 
          offset_el=elevation_min-pitchdeg;        
          }   
      Serial.print("offset_el: ");                //for testing purpose 
      Serial.println(offset_el);                  //for testing porpuse

      // Drive elevation negative until switch is unactivated
      Serial.println("Drive elevation negative until switch is unactivated..");
      while(digitalRead(sensor_el)==HIGH){  
=======
      Pitch_Negative(slowSpeed);                         // Drive negative pitch
      delay(DelayVar);
    }
    Serial.println(F("Switch unactivated"));

    // ################################################################################
    // Caliration of azimuth
    
    Serial.println(F("Starting the Calibration for Azimuth angle"));  
    //FOR THE LOWER MOTOR CONTROLLING THE AZIMUTH
    Serial.println(F("Waiting for the switch to be pushed"));
    while (digitalRead(sensor_az)==LOW){
      Roll_Positive(fastSpeed);
      delay(DelayVar);                                        // Was needed to know for how long to run, delay makes it possible to brake the drive in the middle of a command. 
      getCurrentRoll(DelayVar);                                 // Gets the angles from accelerometer 
     }
    Roll_Brake();                                               // When Sensor_el turns to High, brake
    Serial.println(F("Switch activated"));                   

    // Log offset value                                          
    rolldeg=0;                                                  // Get current angle from the rolldeg which is zero here   
>>>>>>> 634baedf7ae2872d2d2e81165a4a4986bd97237b

    // Drive elevtation negative until switch is unactivated
    Serial.println(F("Drive azimuthal motor negative until switch is unactivated.."));
    while(digitalRead(sensor_az)==HIGH){  

      Roll_Negative(fastSpeed);                                 // Drive Backwards
      delay(DelayVar);
    }
      
<<<<<<< HEAD
Serial.println("Starting the Calibration for Azimuth angle");  
      //FOR THE LOWER MOTOR CONTROLLING THE AZIMUTH
      Serial.println("Waiting for the switch to be pushed");
       while (digitalRead(sensor_az)==LOW){
        Roll_Positive(fastSpeed);
        delay_s(DelayVar);                                //Was needed to know for how long to run, delay_s makes it possible to brake the drive in the middle of a command. 
        getCurrentRoll(DelayVar);                               //Gets the angles from accelerometer 
        }
        Roll_Brake();                                      //When Sensor_el turns to High, brake
        Serial.println("Switch activated");                   
  
        // Log offset value                                          
        rolldeg=0;                               //Get current angle from the rolldeg which is zero here   
  
        // Drive elevtation negative until switch is unactivated
        Serial.println("Drive azimuthal motor negative until switch is unactivated..");
        while(digitalRead(sensor_az)==HIGH){  
  
          Roll_Negative(fastSpeed);                  //Drive Backwards
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
=======
    Serial.println(F("Switch unactivated"));  
 }
>>>>>>> 634baedf7ae2872d2d2e81165a4a4986bd97237b

 Serial.println(F("Ending Calibration"));
 
}

