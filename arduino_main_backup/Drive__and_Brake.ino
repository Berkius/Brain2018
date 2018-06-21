/*
 * All the functions that tells the motor how to run
 * 
 * Date: 2018-06-16
 */

// ROLL
// Create a positive roll motion (lower motor)
void Roll_Positive(int Speed) {
     digitalWrite(roll_IN1,HIGH); 
     digitalWrite(roll_IN2,LOW);  
     analogWrite(roll_PWM,Speed);
}

// Create a negative roll motion (lower motor)
void Roll_Negative(int Speed) {    
     digitalWrite(roll_IN1,LOW); 
     digitalWrite(roll_IN2,LOW);  
     analogWrite(roll_PWM,Speed);
}

// Breake the roll motion (lower motor)
void Roll_Brake(){
     digitalWrite(roll_IN1,LOW); 
     digitalWrite(roll_IN2,HIGH); 
}

// PITCH
// Create a positive pitch motion (upper motor)
void Pitch_Positive(int Speed) {
     digitalWrite(pitch_IN1,HIGH); 
     digitalWrite(pitch_IN2,LOW);  
     analogWrite(pitch_PWM,Speed);
}

// Create a negative pitch motion (upper motor)
void Pitch_Negative(int Speed) {    
     digitalWrite(pitch_IN1,LOW); 
     digitalWrite(pitch_IN2,HIGH);  
     analogWrite(pitch_PWM,Speed);
}

// Breake the pitch motion (upper motor)
void Pitch_Brake(){
     digitalWrite(pitch_IN1,LOW); 
     digitalWrite(pitch_IN2,LOW); 
}
