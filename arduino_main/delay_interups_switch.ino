void delay_s(int total_delay){
/*
 * A delay function which can be intrupted by the switches
 * 
 *
 */

  unsigned long startMillis;                                              // Starting time
  unsigned long currentMillis;                                            // Current time
  const unsigned long period = total_delay;                               // How long the delay should be
  startMillis = millis();                                                 // Define start time
  currentMillis = millis();                                               // Get the current "time"
  int switch_value;                                                       // Value of switch

  // Loop until the total delay is reached
  while (currentMillis - startMillis <= period){
    
    // Read value, then delay 5 ms bacause thats how long it takes to read value
    switch_value = digitalRead(sensor_az);
    delay(7);
    
    // If we reached HIGH value 3 times in a row, trust that value
    if (switch_value == HIGH){
    switch_value_counter += 1;}
    else if (switch_value == LOW){
      switch_value_counter = 0;}

    // If we hit a sensor
    if (digitalRead(sensor_el)==HIGH){
        Serial.println("Pitch switch activated when driving, start calibration of pitch offset");
        End_switches();
        return;                                // Return to main loop (or motor_protocol??)
      }

    // If azimuth switch is activated
    if (switch_value_counter >= 3){
      
      // If the switch was not HIGH the last couple of loops
      if (switch_pre_value == 0){
        switch_count();                       // Check how many laps it have turned and make action if rotated too much
        switch_pre_value= 1;                  // Set switch value to activated 
      } 
    }
    else if(switch_value_counter < 3){
      switch_pre_value = 0;                   // Set switch value to unactivated 
    }

    currentMillis = millis();                                             // Get the new current "time"
    
    }
  }
