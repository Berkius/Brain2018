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
  
  Serial.println("Entering Calibration");

 // Starting the calibration if both sensor are unactivated    
 if ((digitalRead(sensor_el)==LOW) || (digitalRead(sensor_az)==LOW)){      

    // ##################################################
    // Calibration of accelerometer
    
    // Drive pitch motor until hitting switch
    Serial.println("Drive pitch motor until hitting switch..");         
    while (digitalRead(sensor_el)==LOW){                  // When the pitch switch is low 
      Pitch_Positive(fastSpeed);                          // Drive positive direetion
      delay(DelayVar);                                    // Was needed to know for how long to run
      getCurrentPitch();                                  // Gets the angles from accelerometer 
    }
      
    Pitch_Brake();                                        // When Sensor_el turns to High, brake
    Serial.println("Switch activated");                   

    // Log offset value                                          
    getCurrentPitch();                                    // Get current angle from the accelerometer  
    if (elevation_min!=pitchdeg){                         // If they are not equal save the offset 
        offset_el=abs(elevation_min-pitchdeg);        
        }   
    Serial.print("offset_el: ");                          // For testing purpose 
    Serial.println(offset_el);                            // For testing porpuse

    // Drive elevtation negative until switch is unactivated
    Serial.println("Drive elevtation negative until switch is unactivated..");
    while(digitalRead(sensor_el)==HIGH){  

      Pitch_Negative(slowSpeed);                         // Drive negative pitch
      delay_s(DelayVar);
    }
    Serial.println("Switch unactivated");

    // ################################################################################
    // Caliration of azimuth
    
    Serial.println("Starting the Calibration for Azimuth angle");  
    //FOR THE LOWER MOTOR CONTROLLING THE AZIMUTH
    Serial.println("Waiting for the switch to be pushed");
    while (digitalRead(sensor_az)==LOW){
      Roll_Positive(fastSpeed);
      delay_s(DelayVar);                                        // Was needed to know for how long to run, delay_s makes it possible to brake the drive in the middle of a command. 
      getCurrentRoll(DelayVar);                                 // Gets the angles from accelerometer 
     }
    Roll_Brake();                                               // When Sensor_el turns to High, brake
    Serial.println("Switch activated");                   

    // Log offset value                                          
    rolldeg=0;                                                  // Get current angle from the rolldeg which is zero here   

    // Drive elevtation negative until switch is unactivated
    Serial.println("Drive azimuthal motor negative until switch is unactivated..");
    while(digitalRead(sensor_az)==HIGH){  

      Roll_Negative(fastSpeed);                                 // Drive Backwards
      delay_s(DelayVar);
      //Serial.println("inside high loop");
    }
      
    Serial.println("Switch unactivated");  
 }

 Serial.println("Ending Calibration");
 
}

