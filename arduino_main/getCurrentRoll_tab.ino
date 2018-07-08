void getCurrentRoll(){
/*
 * Updates the roll angle of the motors
 * 
 * It does this by taking the angular velocity of the motors (from the gyroscope, IMU) and the time the motors have been driving to calculate the angle the motors should have
 * 
 * Date: 2018-07-08
 */

  float change_in_roll;

  // Check rotation speed
  float angular_velocity_roll = Check_angular_velocity_roll();

  int time_roll =  millis() - DrivingTimeStart;                 // Time since we started the motors
  DrivingTimeStart = millis();                              // Restarting time motors
  
  change_in_roll = time_roll*0.001 * angular_velocity_roll;
  
  rolldeg = rolldeg + change_in_roll;

  //Serial.print("roll angle: ");
  //Serial.println(rolldeg);
  
}
