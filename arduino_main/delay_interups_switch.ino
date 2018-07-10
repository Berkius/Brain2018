void delay_s(int total_delay){
/*
 * A delay function which can be intrupted by the switches
 * 
 * Date: 2018-07-08
 */

  unsigned long startMillis;                                              // Starting time
  unsigned long currentMillis;                                            // Current time
  const unsigned long period = total_delay;                               // How long the delay should be
  startMillis = millis();                                                 // Define start time
  currentMillis = millis();                                               // Get the current "time"

  // Loop until the total delay is reached
  while (currentMillis - startMillis <= period){
    
    // If we reached HIGH value counter_max times in a row, trust that value
    counter_az();
    counter_el();
    
    // If we hit a sensor
    if (switch_value_counter_el >= counter_max){
        Serial.println("Pitch switch activated when driving, start calibration of pitch offset");
        End_switches();
        return;                                // Return to main loop (or motor_protocol??)
      }

    // If azimuth switch is activated
    if (switch_value_counter_az >= counter_max){
      
      // If the switch was not HIGH the last couple of loops
      if (switch_pre_value == 0){
        switch_count();                       // Check how many laps it have turned and make action if rotated too much
        switch_pre_value= 1;                  // Set switch value to activated 
      } 
    }
    else if(switch_value_counter_az_low >= counter_max){
      switch_pre_value = 0;                   // Set switch value to unactivated 
    }

    currentMillis = millis();                                             // Get the new current "time"
    
    }
  }
