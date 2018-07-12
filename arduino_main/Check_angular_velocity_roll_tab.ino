int Check_angular_velocity_roll(){
/*
 * Calculate the angular velocity for the roll motor using the gyroscope
 * 
 * Date: 2018-06-29
 */
   
  float angular_velocity_roll;

  float cosPitch = cos((pitchdeg-offset_el)*PI/180);
  float sinPitch = sin((pitchdeg-offset_el)*PI/180);

  gyro.readGyro(&gx, &gy, &gz);                           // Read data from gyro

  angular_velocity_roll = (gx * (-sinPitch) +gz * (-cosPitch)) * 1.07;   // Rotation around vertical axis
  // Add about 10% to compensate for too low values from gyroscope (or time issue)
  // no compensation here will make it bad at large increments
  
  return angular_velocity_roll;
}

