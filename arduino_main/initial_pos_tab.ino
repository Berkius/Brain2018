void initial_pos(){
/*
 * Drives the parabola back to initial position and calibrate
 * 
 * Date: 2018-07-08
 */

  Pitch_Brake();
  Roll_Brake();

  DrivingTimeStart = millis();                              // Starting time motors
  
  // Rotate past switch if needed
  while (switch_count_az == -1){
    Roll_Positive(fastSpeed);
    delay_s(100);
    getCurrentRoll();
    }
  
  // DRIVE ROLL MOTOR POSITVE UTILL UNACTIVATED
  DrivingTimeStart = millis();                                // Starting time motors
  Serial.print(F("Drive roll motor positive until switch is unactivated and without safety margin.."));
  while(switch_value_counter_az >= counter_max){  
    Roll_Positive(slowSpeed);                                 // Drive Backwards
    //delay(DelayVar);
    counter_az();
  } 
  Roll_Brake();

  Calibration();

}
