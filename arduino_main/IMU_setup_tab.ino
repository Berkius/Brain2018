void IMU_setup(){
/*
 * Calibrate the accelerometer
 * 
 * Date: 2018-06-16
 */

 
// ########################################################
// ACCELEROMETER SETUP

  Serial.println("Starting accelerometer setup..");
 
 for (int i = 0; i <= 200; i++) {
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
 }
 Serial.println("accelerometer setup done");

 // ###########################################
 // GYROSCOPE SETUP

  Serial.print("Starting gyroscope setup..     ");
  gyro.init(ITG3200_ADDR_AD0_LOW);
  gyro.zeroCalibrate(2500, 2);    // 2 sample 2500 ms/sample
  Serial.println("Gyroscope setup done");
 
}

