/*
 * All the functions that tells the motor how to run
 * 
 * Date: 2018-06-16
 */

// ROLL
// Create a positive roll motion (lower motor)
void Roll_Positive(int Speed) {
  int safe_marg = 5;
  if (rolldeg < azimuth_max - safe_marg){
     //Serial.println("Entering Roll_Positive");
     motor_direction=3;  //drive forward roll
     digitalWrite(roll_IN1,HIGH); 
     digitalWrite(roll_IN2,LOW);  
     analogWrite(roll_PWM,Speed);
     //Serial.println("Ending Roll_Positive");
     //ROLL_T++;
  }
  else{
    Serial.println("Roll reached maximum value");
    }
  }

// Create a negative roll motion (lower motor)
void Roll_Negative(int Speed) {    
  int safe_marg = 5;
  if (rolldeg >= azimuth_min + safe_marg){
     //Serial.println("Entering Roll_Negative");
     motor_direction=4;  //drive backwards roll
     digitalWrite(roll_IN1,LOW); 
     digitalWrite(roll_IN2,LOW);  
     analogWrite(roll_PWM,Speed);
     //Serial.println("Ending Roll_Negative");
  }
  else{
    Serial.println("Roll reached minimum value");
  }
 }

// Breake the roll motion (lower motor)
void Roll_Brake(){
     //Serial.println("Entering Roll_Brake");
     digitalWrite(roll_IN1,LOW); 
     digitalWrite(roll_IN2,HIGH); 
     //Serial.println("Ending Roll_Brake");
}

// PITCH
// Create a positive pitch motion (upper motor)
void Pitch_Positive(int Speed) {
  int safe_marg = 5;
  if (pitchdeg < elevation_max - safe_marg){
     //Serial.println("Entering Pitch_Positive");
     motor_direction=1;  //drive forward pitch
     digitalWrite(pitch_IN1,HIGH); 
     digitalWrite(pitch_IN2,LOW);  
     analogWrite(pitch_PWM,Speed);
     //Serial.println("Ending Pitch_Positive");
  }
  else{
    Serial.println("Pitch reached maximum value");
    }
}

// Create a negative pitch motion (upper motor)
void Pitch_Negative(int Speed) {  
  int safe_marg = 5;
  if (pitchdeg >= elevation_min + safe_marg){
     //Serial.println("Entering Pitch_Negative");
     motor_direction=2; //drive backwards pitch
     digitalWrite(pitch_IN1,LOW); 
     digitalWrite(pitch_IN2,HIGH);  
     analogWrite(pitch_PWM,Speed);
     //Serial.println("Ending Pitch_Negative");
  }
  else{
  Serial.println("Pitch reached minimum value");
  }
 }


// Breake the pitch motion (upper motor)
void Pitch_Brake(){
     //Serial.println("Entering Pitch_Brake");
     digitalWrite(pitch_IN1,LOW); 
     digitalWrite(pitch_IN2,LOW); 
     //Serial.println("Ending Pitch_Brake");
}

