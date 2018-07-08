 int counter_az(){
/*
 * Counts the number of times in a row the az sensor has been high
 *  
 * Date: 2018-07-08
 */

  int switch_az_value;
 
 for(int i=0; i<=3; i++){
    switch_az_value = digitalRead(sensor_az);
    delay(10);

    if (switch_az_value == HIGH){
      switch_az_value_counter += 1; 
    }
    else{
      switch_az_value_counter = 0;
    }
  }

  return switch_az_value_counter;
 }

// ###############################################
int counter_el(){
/*
 * Counts the number of times in a row the az sensor has been high
 * 
 * Date: 2018-07-08
 */

  int switch_el_value;

  for(int i=0; i<=3; i++){
      switch_el_value = digitalRead(sensor_el);
      delay(10);
  
      if (switch_el_value == HIGH){
        switch_el_value_counter += 1;     
      }
      else{
        switch_el_value_counter = 0;
      }
      
    return switch_el_value_counter;
  
   }
}
