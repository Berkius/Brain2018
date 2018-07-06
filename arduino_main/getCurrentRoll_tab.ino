void getCurrentRoll(int time_roll){

  float change_in_roll;

  // Check rotation speed
  float angular_velocity_roll = Check_angular_velocity_roll();
  
  change_in_roll = time_roll*0.001 * angular_velocity_roll;
  
  rolldeg = rolldeg + change_in_roll;

  //Serial.print("roll angle: ");
  //Serial.println(rolldeg);
  
}
