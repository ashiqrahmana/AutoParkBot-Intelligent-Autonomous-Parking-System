void left_turn(){
  //turnleft
  leftServo.write(90 - back_flag*wheel_speed);
  rightServo.write(90 + back_flag*wheel_speed);    
  Serial.println("slightly forward");
  delay(500);
  leftServo.write(90 - back_flag*wheel_speed);
  rightServo.write(90 - back_flag*wheel_speed);    
  Serial.println("turning left");
  delay(1000);
  if (center_ir == 1){
    basic_flag = 1;
    Serial.println("setting basic flag to one");
  }
}

void right_turn(){
  //turnright
  leftServo.write(90 - back_flag*wheel_speed);
  rightServo.write(90 + back_flag*wheel_speed);    
  Serial.println("slightly forward");
  delay(250);
  leftServo.write(90 + back_flag*wheel_speed);  
  rightServo.write(90 + back_flag*wheel_speed);    
  Serial.println("turning right");
  delay(1050);
    basic_flag = 1;
    Serial.println("setting basic flag to one");
}

void u_turn(){
  //turnright
  leftServo.write(90 + back_flag*wheel_speed);
  rightServo.write(90 + back_flag*wheel_speed);    
  Serial.println("Uturn");
  delay(900*2);
  basic_flag = 1;
  Serial.println("setting basic flag to one");
}
