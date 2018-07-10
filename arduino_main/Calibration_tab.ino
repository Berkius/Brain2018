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
  int DelayVar= 30;

  counter_az();
  counter_el();
  
  //Serial.println(F("Entering Calibration"));

 // Starting the calibration if both sensor are unactivated    
 if ((switch_value_counter_el <= counter_max) || (switch_value_counter_az <= counter_max)){      

    // ##################################################
    // Calibration of accelerometer

    Serial.println(F("Starting the Calibration for Elevation angle"));
    
    // DRIVE PITCH MOTOR NEGATIVE UNTIL HITTING SWITCH
    Serial.print(F("Drive pitch motor negative until hitting switch.."));         
    while (switch_value_counter_el < counter_max){                             // When the pitch switch is low 
      // Drive negative direction
      Pitch_Negative(slowSpeed);                             
      counter_el();
    }    
    Pitch_Brake();  
    // When Sensor_el turns to High, brake
    Serial.println(F("Switch activated"));  

   // while(1==1){}

     // ######################
    // IMU FUNCTION SETUP
    IMU_setup();  
    // #######################
    
    getCurrentPitch();                                         // Gets the angles from accelerometer 
    // LOG OFFSET VALUE                                       
    getCurrentPitch();                                         // Get current angle from the accelerometer  
    offset_el=elevation_min-pitchdeg;                          // Save value
    getCurrentPitch();                                         // Get current angle from the accelerometer 
    Serial.print(F("Pitch angle: "));   
    Serial.println(pitchdeg);                 
  
    // DRIVE ELEVATION POSITIVE UNTIL SWITCH IS UNACTIVATED
    Serial.print("Drive pitch positive until switch is unactivated and within safety margin..");
    while(switch_value_counter_el >= counter_max){  
      Pitch_Positive(slowSpeed);                              // Drive positive pitch
      //delay(DelayVar);
      counter_el();
    }
   

    // Run pitch positive until within safety margin
    while(pitchdeg < safe_marg+elevation_min){
       Pitch_Positive(slowSpeed);                              // Drive positive pitch
      // LOG OFFSET VALUE                                       
      delay(DelayVar);
      getCurrentPitch();       
    }
    
    Serial.println(F("Switch unactivated and without safety margin"));
    Pitch_Brake();

    // ################################################################################
    // Calibration of azimuth

    Serial.println(F("Starting the Calibration for Azimuth angle"));  

    // DRIVE ROLL MOTOR NEGATIVE UNTIL HITTING SWITCH
    Serial.print(F("Drive roll motor negative until hitting switch.."));
    DrivingTimeStart = millis();                              // Starting time motors
    while (switch_value_counter_az < counter_max){
      Roll_Negative(fastSpeed);
      //delay(DelayVar);                                          // How long to run before checking switches 
      getCurrentRoll();                                          // Gets the angles from gyroscope 
      counter_az();
     }
    Roll_Brake();                                               // When Sensor_az turns to High, brake
    Serial.println(F("Switch activated"));   
    Serial.print(F("Roll angle: "));   
    Serial.println(rolldeg);                

    // LOG ROLL DEGREE                                         
    rolldeg=0;                                                  // Get current angle from the rolldeg which is zero here   
   //
   //while(1==1){}

    // DRIVE ROLL MOTOR POSITVE UTILL UNACTIVATED
    DrivingTimeStart = millis();                              // Starting time motors
    Serial.print(F("Drive roll motor positive until switch is unactivated and without safety margin.."));
    while(switch_value_counter_az >= counter_max){  
      Roll_Positive(slowSpeed);                                 // Drive Backwards
      //delay(DelayVar);
      counter_az();
    } 
     // Run roll positive until within safety margin
     while(rolldeg < safe_marg){
       Roll_Positive(slowSpeed);                              // Drive positive pitch
      // LOG OFFSET VALUE                                       
      delay(DelayVar);
      getCurrentRoll();       
    }
    Roll_Brake();
    Serial.println(F("Switch unactivated and without safety margin"));  
 }
 else{
    Serial.println(F("One of the switches are activated, can't run calibration"));
 }


 calibration_done = 1;

 //Serial.println(F("Ending Calibration"));
  safe_marg = 3;

  switch_value_counter_az = 0;
  switch_value_counter_el = 0;
 
}

