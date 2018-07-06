/*
 * All the functions that tells the motor how to run
 * 
 * Date: 2018-06-16
 */

// ROLL
// Create a positive roll motion (lower motor)
void Roll_Positive(int Speed) {
     //Serial.println("Entering Roll_Positive");
     motor_direction_2=1;  //drive forward roll/azimuth
     digitalWrite(roll_IN1,LOW); 
     digitalWrite(roll_IN2,HIGH);  
     analogWrite(roll_PWM,Speed);
     //Serial.println("Ending Roll_Positive");
  }

// Create a negative roll motion (lower motor)
void Roll_Negative(int Speed) {    
     //Serial.println("Entering Roll_Negative");
     motor_direction_2=2;  //drive backwards roll
     digitalWrite(roll_IN1,HIGH); 
     digitalWrite(roll_IN2,LOW);  
     analogWrite(roll_PWM,Speed);
     //Serial.println("Ending Roll_Negative");
 }

// Breake the roll motion (lower motor)
void Roll_Brake(){
     //Serial.println("Entering Roll_Brake");
     digitalWrite(roll_IN1,LOW); 
     digitalWrite(roll_IN2,LOW); 
     //Serial.println("Ending Roll_Brake");
     delay(200);
}

// PITCH
// Create a positive pitch motion (upper motor)
void Pitch_Positive(int Speed) {
  if (calibration_done == 0){
       motor_direction_1=1;  //drive forward pitch
       digitalWrite(pitch_IN1,LOW); 
       digitalWrite(pitch_IN2,HIGH);  
       analogWrite(pitch_PWM,Speed);
  }
  else{
    if (pitchdeg <= elevation_max - safe_marg){
       //Serial.println("Entering Pitch_Positive");
       motor_direction_1=1;  //drive forward pitch
       digitalWrite(pitch_IN1,LOW); 
       digitalWrite(pitch_IN2,HIGH);  
       analogWrite(pitch_PWM,Speed);
       //Serial.println("Ending Pitch_Positive");
    }
    else{
      Pitch_Brake();
      Serial.println(F("Pitch reached maximum value"));
      }
  }
}

// Create a negative pitch motion (upper motor)
void Pitch_Negative(int Speed) { 
  if  (calibration_done == 0){
     motor_direction_1=2; //drive backwards pitch
     digitalWrite(pitch_IN1,HIGH); 
     digitalWrite(pitch_IN2,LOW);  
     analogWrite(pitch_PWM,Speed);
  }
  else{    
      if (pitchdeg >= elevation_min + safe_marg){
         //Serial.println("Entering Pitch_Negative");
         motor_direction_1=2; //drive backwards pitch
         digitalWrite(pitch_IN1,HIGH); 
         digitalWrite(pitch_IN2,LOW);  
         analogWrite(pitch_PWM,Speed);
         //Serial.println("Ending Pitch_Negative");
      }
      else{
      Pitch_Brake();
      Serial.print(F("Pitch reached minimum value ("));
      Serial.print(elevation_min + safe_marg);
      Serial.print(", our value: ");
      Serial.print(pitchdeg);
      Serial.println(")");
      }
  }
 }


// Breake the pitch motion (upper motor)
void Pitch_Brake(){
     //Serial.println("Entering Pitch_Brake");
     digitalWrite(pitch_IN1,LOW); 
     digitalWrite(pitch_IN2,LOW); 
     //Serial.println("Ending Pitch_Brake");
     delay(200);
}

