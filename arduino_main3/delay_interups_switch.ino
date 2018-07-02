void delay_s(int total_delay){
/*
 * A delay function which can be intrupted by the switches
 * 
 * OBS, Send only in tens of ms (like 20 or 340 NOT 234)
 */

  int remaining_delay = total_delay;

  // Run ten ms when check switches
  while (remaining_delay > 9){
    Serial.println("delaaaay_s");
    Serial.println(digitalRead(sensor_el));
    

    // If we hit a sensor
    if (digitalRead(sensor_el)==HIGH){
        Serial.println("Pitch switch activated while delayed");
        delay(3000); // TEST REMOVE LATER
        End_switches();
      }
    if (digitalRead(sensor_az)==HIGH){
        switch_count();       //Check how many laps it have turned and if it
      }  

    // Remove 10ms from remaining delay
    remaining_delay -=  10;
    
    }
  }
