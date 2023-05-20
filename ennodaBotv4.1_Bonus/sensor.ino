void ultra() {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration_ultra = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration_ultra * 0.034 / 2;
  //Serial.println(distance);
}

// IR sensor 
void callibration(){  
  Serial.println("Place all the sensors in white, Enter ok to continue");
  while(true){
      if (Serial.available()>1){
        low_l = RCTime(left);
        low_r = RCTime(right);
        low_c = RCTime(ctr);
        break;
      }
  }
  
  Serial.println("Place all the sensors in black, Enter ok to continue");
  while(true){
    if (Serial.available()>3){
        high_l = RCTime(left);
        high_r = RCTime(right);
        high_c = RCTime(ctr);
        break;
      }
  }
  mid_l = (low_l + high_l)/4;
  mid_c = (low_c + high_c)/4;
  mid_r = (low_r + high_r)/4;
}

long RCTime(int sensorIn) {
  long duration = 0;
  pinMode(sensorIn, OUTPUT); // Sets pin as OUTPUT
  digitalWrite(sensorIn, HIGH); // Pin HIGH
  delay(1); // Waits for 1 millisecond
  pinMode(sensorIn, INPUT); // Sets pin as INPUT
  digitalWrite(sensorIn, LOW); // Pin LOW
  while(digitalRead(sensorIn)) { // Waits for the pin to go LOW
    duration++;
  }
  return duration; // Returns the duration of the pulse
}

void ir_read(){
  left_ir = RCTime(left);
  center_ir = RCTime(ctr);
  right_ir = RCTime(right);
  
  if(left_ir > mid_l)
    left_ir = 1;
  else
    left_ir = 0;
    
  if(right_ir > mid_r)
    right_ir = 1;
  else
    right_ir = 0;
  
  if(center_ir > mid_c)
    center_ir = 1;
  else
    center_ir = 0;
  Serial.print(String(left_ir)+" "+ String(center_ir)+" "+String(right_ir) + "     " + String(basic_counter)+ "     " + String(right_flag)+ "     " + String(left_flag) + "   " + String(obstacle_counter) + "   " +String(len_counter));
  Serial.print("\t\t");
}
