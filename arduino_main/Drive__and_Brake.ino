/*
 * All the functions that tells the motor how to run
 * 
 * Date: 2018-06-16
 */

// ROLL
// Create a positive roll motion (lower motor)
void Roll_Positive(int Speed) {
     //Serial.println("Entering Roll_Positive");
     digitalWrite(roll_IN1,HIGH); 
     digitalWrite(roll_IN2,LOW);  
     analogWrite(roll_PWM,Speed);
     //Serial.println("Ending Roll_Positive");
}

// Create a negative roll motion (lower motor)
void Roll_Negative(int Speed) {    
     //Serial.println("Entering Roll_Negative");
     digitalWrite(roll_IN1,LOW); 
     digitalWrite(roll_IN2,LOW);  
     analogWrite(roll_PWM,Speed);
     //Serial.println("Ending Roll_Negative");
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
     //Serial.println("Entering Pitch_Positive");
     motor_direction=1;  //drive forward 
     digitalWrite(pitch_IN1,HIGH); 
     digitalWrite(pitch_IN2,LOW);  
     analogWrite(pitch_PWM,Speed);
     //Serial.println("Ending Pitch_Positive");
}

// Create a negative pitch motion (upper motor)
void Pitch_Negative(int Speed) {  
     //Serial.println("Entering Pitch_Negative");
     motor_direction=2; //drive backwards   
     digitalWrite(pitch_IN1,LOW); 
     digitalWrite(pitch_IN2,HIGH);  
     analogWrite(pitch_PWM,Speed);
     //Serial.println("Ending Pitch_Negative");
}

// Breake the pitch motion (upper motor)
void Pitch_Brake(){
     //Serial.println("Entering Pitch_Brake");
     digitalWrite(pitch_IN1,LOW); 
     digitalWrite(pitch_IN2,LOW); 
     //Serial.println("Ending Pitch_Brake");
}
