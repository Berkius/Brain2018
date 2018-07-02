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
  int DelayVar=100;
  
  Serial.println(F("Entering Calibration"));

 // Starting the calibration if both sensor are unactivated    
 if ((digitalRead(sensor_el)==LOW) || (digitalRead(sensor_az)==LOW)){      

    // ##################################################
    // Calibration of accelerometer
    
    // DRIVE PITCH MOTOR NEGATIVE UNTIL HITTING SWITCH
    Serial.println(F("Drive pitch motor negative until hitting switch.."));         
    while (digitalRead(sensor_el)==LOW){                      // When the pitch switch is low 
      Pitch_Negative(fastSpeed);                              // Drive negative direetion
      delay(DelayVar);                                        // How long to run before checking switch
      getCurrentPitch();                                      // Gets the angles from accelerometer 
    }    
    Pitch_Brake();                                             // When Sensor_el turns to High, brake
    Serial.println(F("Switch activated"));                   

    // LOG OFFSET VALUE                                       
    getCurrentPitch();                                         // Get current angle from the accelerometer  
    offset_el=abs(elevation_min-pitchdeg);                     // Save value
    
    // DRIVE ELEVATION POSITIVE UNTIL SWITCH IS UNACTIVATED
    Serial.println("Drive pitch positive until switch is unactivated..");
    while(digitalRead(sensor_el)==HIGH){  
      Pitch_Positive(slowSpeed);                         // Drive positive pitch
      delay(DelayVar);
    }
    Serial.println(F("Switch unactivated"));
    Pitch_Brake();

    // ################################################################################
    // Calibration of azimuth

    Serial.println(F("Starting the Calibration for Azimuth angle"));  

    // DRIVE ROLL MOTOR NEGATIVE UNTIL HITTING SWITCH
    Serial.println(F("Drive roll motor positive until hitting switch.."));
    while (digitalRead(sensor_az)==LOW){
      Roll_Positive(fastSpeed);
      delay(DelayVar);                                          // How long to run before checking switches 
      getCurrentRoll(DelayVar);                                 // Gets the angles from gyroscope 
     }
    Roll_Brake();                                               // When Sensor_az turns to High, brake
    Serial.println(F("Switch activated"));                   

    // LOG ROLL DEGREE                                         
    rolldeg=0;                                                  // Get current angle from the rolldeg which is zero here   

    // DRIVE ROLL MOTOR NEGATIVE UTILL UNACTIVATED
    Serial.println(F("Drive roll motor negative until switch is unactivated.."));
    while(digitalRead(sensor_az)==HIGH){  
      Roll_Negative(fastSpeed);                                 // Drive Backwards
      delay(DelayVar);
    }      
    Roll_Brake();
    Serial.println(F("Switch unactivated"));  
 }
 else{
    Serial.println(F("One of the switches are activated, can't run calibration"));
 }

 Serial.println(F("Ending Calibration"));
 
}

