int Check_angular_velocity_roll(){
<<<<<<< HEAD
=======
/*
 * Calculate the angular velocity for the roll motor using the gyroscope
 * 
 * Date: 2018-06-29
 */
   
>>>>>>> 634baedf7ae2872d2d2e81165a4a4986bd97237b
  float angular_velocity_roll;

  float cosPitch = cos(pitchdeg*PI/180);
  float sinPitch = sin(pitchdeg*PI/180);

  gyro.readGyro(&gx, &gy, &gz);                           // Read data from gyro

  angular_velocity_roll = gx * sinPitch +gz * cosPitch;   // Rotation around veritcal axis
  
<<<<<<< HEAD
  
  return angular_velocity_roll;
}

=======
  return angular_velocity_roll;
}

>>>>>>> 634baedf7ae2872d2d2e81165a4a4986bd97237b