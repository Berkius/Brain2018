void delay_s(int total_delay){
/*
 * A delay function which can be intrupted by the switches
 * 
 * OBS, Send only in tens of ms (like 20 or 340 NOT 234)
 */

  int remaining_delay = total_delay;

  // Run ten ms when check switches
  while (remaining_delay > 9){
    delay(10);

    // If we hit a sensor, calibrate again
    if ((sensor_el==HIGH) && (sensor_az==HIGH)){
      Calibration();
      break;
      }

    // Remove 10ms from remaining delay
    remaining_delay -=  10;
    
    }
  }
