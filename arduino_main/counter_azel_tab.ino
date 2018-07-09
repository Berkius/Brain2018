 int counter_az(){
/*
 * Counts the number of times in a row the az sensor has been high
 *  
 * Date: 2018-07-08
 */

  int switch_az_value;
 
 for(int i=0; i<counter_max; i++){
    switch_az_value = digitalRead(sensor_az);
    delay(10);
    
    if (switch_az_value == HIGH){
      switch_value_counter_az += 1; 
      switch_value_counter_az_low = 0;
    }
    else if (switch_az_value == LOW){
      switch_value_counter_az = 0;
      switch_value_counter_az_low += 1; 
    }

   // Serial.print("az HIGH value: ");
   // Serial.println(switch_value_counter_az);
  }
 }

// ###############################################

int counter_el(){
/*
 * Counts the number of times in a row the az sensor has been high
 * 
 * Date: 2018-07-08
 */

  int switch_el_value;

  for(int i=0; i<counter_max; i++){
      switch_el_value = digitalRead(sensor_el);
      delay(10);
  
      if (switch_el_value == HIGH){
        switch_value_counter_el += 1;
        switch_value_counter_el_low = 0;     
      }
      else if(switch_el_value == LOW){
        switch_value_counter_el = 0;
        switch_value_counter_el_low += 1; 
      }

  
  }
}
// ###############################################

void reset_counters(){

  switch_value_counter_az = 0;
  switch_value_counter_az_low = 0;
  switch_value_counter_el = 0;
  switch_value_counter_el_low = 0;
  
  }
