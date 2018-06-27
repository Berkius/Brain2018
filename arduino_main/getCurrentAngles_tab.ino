void getCurrentAngles(){
/*
 * Calculate the pitch and roll angle with sensor data from the accelerometer
 * 
 * Date: 2018-06-16
 */
 //Serial.println("Entering getCurrentAngles");

// code fragment for Accelerometer angles (roll and pitch)
  acc.readAccel(&ax, &ay, &az); //read the accelerometer values and store them in variables  x,y,z
  rawX = ax - aoffsetX;
  rawY = ay - aoffsetY;
  rawZ = az  - (255 - aoffsetZ);
  
  X = rawX/256.00; // used for angle calculations
  Y = rawY/256.00; // used for angle calculations
  Z = rawZ/256.00; // used for angle calculations

  // calculated angle in radians
  rollrad = atan(Y/sqrt(X*X+Z*Z));  
  pitchrad = atan(X/sqrt(Y*Y+Z*Z));
  
  // calculated angle in degrees (OBS in calibration offset will be zero) 
  rolldeg = 180*(atan(Y/sqrt(X*X+Z*Z)))/PI + offset_az; 
  pitchdeg = 180*(atan(X/sqrt(Y*Y+Z*Z)))/PI + offset_el; 

  // Print angles for debugging
  //Serial.print("Pitch angle: ");
  //Serial.println(pitchdeg);
  //Serial.println("Ending getCurrentAngles");
}
