int Check_angular_velocity_roll(){
  float angular_velocity_roll;

  float cosPitch = cos(pitchdeg*PI/180);
  float sinPitch = sin(pitchdeg*PI/180);

  gyro.readGyro(&gx, &gy, &gz);                           // Read data from gyro

  angular_velocity_roll = gx * sinPitch +gz * cosPitch;   // Rotation around veritcal axis
  
  
  return angular_velocity_roll;
}

