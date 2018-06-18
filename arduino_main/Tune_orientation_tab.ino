/* Runs the motor a few time units, then check the delta angle (between satetlite position and our position), 
 *  repeat until the delta angle is less than the tolerance
 *  
 *  Run this program after Coarse_adjust_position.io when starting to track a new satelite and when updating 
 *  position when tracking a satelite (when delta angle has become too high)
 * 
 * Date: 2018-06-15
 */

 void Tune_orientation(){

  // SHOULD WE UPDATE SATEOLITE POS EVERYTIME ASWELL?
  
  // %%%%%%%%%%%%%%%%
   //GET rolldeg and pitchdeg HERE
   // %%%%%%%%%%%%%%%%%
   
  
  delta_roll = AZ_degree-rolldeg;
  delta_pitch = EL_degree-pitchdeg;
  
  // Tolerance: How big is delta_roll/delta_pitch allowed to be
  int tol = 0.5; // [degree] - CHANGE TO WANTED VALUE
  
  // Speed of the motors, PWM setting 0-255
  int Speed = 100; // CHANGE VELOCITY

  int time_roll = 20; // How long to run the motor for roll [ms]
  int time_pitch = 20; // How long to run the motor for roll [ms]
  
  // Run roll motor while outside the tolerance
  while (delta_roll > tol){
  
     // If we want positive or negative roll
    if (delta_roll > 0){
      Roll_Positive(time_roll);}
    else{
      Roll_Negative(time_roll);}
  
     // For how long time we should drive the roll motor before updating values
     delay(100);
  
    // Update roll angle
    // %%%%%%%%%%%%%%%%%%%
    // UPDATE ANGLES HERE
    // %%%%%%%%%%%%%%%
    
    // Calculate new delta roll angle
    delta_roll = AZ_degree-rolldeg;
  
    // Printing for debugging, delta_roll should be smaller every loop
    Serial.println(delta_roll);
  }
  // Break roll velocity after reaching wanted orientation
  Pitch_Brake();
  delay(100);
  
  // Run pitch motor until within the tolerance
  while (delta_pitch > tol){
  
     // If we want positive or negative roll
    if (delta_pitch > 0){
      Roll_Positive(time_pitch);}
    else{
      Roll_Negative(time_pitch);}
  
    // For how long time we should drive the pitch motor before updating values
    delay(100);
    
  
    // Update roll angle, send in the adress for the pitchdeg and rolldeg
    getCurrentAngles();
    
    // Calculate new delta pitcj angle
    delta_pitch = EL_degree-pitchdeg;
  
    // Printing for debugging, delta_roll should be smaller every loop
    Serial.println(delta_roll);
  }
  // Break pitch velocity after reaching wanted orientation
  Pitch_Brake();
  delay(100);
}
