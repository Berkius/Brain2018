
int counter_el(){
/*
 * Counts the number of times in a row the el sensor has been high
 * 
 * Date: 2018-07-08
 */

  int switch_el_value;

  for(int i=0; i<4; i++){
      switch_el_value = digitalRead(sensor_el);
      delay(10);
      //Serial.println(switch_value_counter_el);
  
      if (switch_el_value == HIGH){
        switch_value_counter_el += 1;  
      }
      else if(switch_el_value == LOW){
        switch_value_counter_el = 0;
      }
  }
}

