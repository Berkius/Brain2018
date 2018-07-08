void IMU_setup(){
/*
 * Setup the IMU (accelerometer & gyroscope)
 * 
 * Setup accelerometer:  power on the accelerometer, the calibration of the horizontal plane is turned off 
 * 
 * Setup gyroscope: Have completly still for 5 sec to calibrate that angular velocity to zero
 * 
 * Date: 2018-06-16
 */

 
// ########################################################
// ACCELEROMETER SETUP

  Serial.print("Starting accelerometer setup..");

 acc.powerOn();
 
/* for (int i = 0; i <= 200; i++) {
  acc.readAccel(&ax, &ay, &az);
  
  if (i == 0) {
    aoffsetX = ax;
    aoffsetY = ay;
    aoffsetZ = az;
  }
  if (i > 1) {
    aoffsetX = (ax + aoffsetX) / 2;
    aoffsetY = (ay + aoffsetY) / 2;
    aoffsetZ = (az + aoffsetZ) / 2;
  }
 }*/
 
 Serial.println("accelerometer setup done");

 // ###########################################
 // GYROSCOPE SETUP

// Setup gyroscope 
  Serial.print("Gyro setup..     ");
  gyro.init(ITG3200_ADDR_AD0_LOW);
  gyro.zeroCalibrate(1000, 2);    // 1000 samples, 2ms per sample
  Serial.println("Gyro setup done");
 
}

