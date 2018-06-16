/*
 * Calibrate the accelerometer
 * 
 * Date: 2018-06-16
 */

void accelerometer_setup(){
 acc.powerOn();
 
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
}

