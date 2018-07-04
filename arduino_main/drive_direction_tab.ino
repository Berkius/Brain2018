void drive_direction(int delta, int motor, int Speed){
/*
 * A program which decied which way is the shortest to go for the motors to the satelite angle
 * 
 * Motor 0 == pitch 
 * Motor 1 == roll
 * 
 */

// If pitch motor
if (motor == 0){
  if (((delta > 0) && (abs(delta) <= 180)) || ((delta < 0) && (abs(delta) >= 180))){
    Pitch_Positive(Speed);}
   else if (((delta > 0) && (delta > 180)) || ((delta < 0) && (delta < 180))){
    Pitch_Negative(Speed);}
  }

// If roll motor
else if (motor ==1){
  if (((delta > 0) && (abs(delta) <= 180)) || ((delta < 0) && (abs(delta) >= 180))){
    Roll_Positive(Speed);}
 else if (((delta > 0) && (delta > 180)) || ((delta < 0) && (delta < 180))){
    Roll_Negative(Speed);}
  
  }



}
