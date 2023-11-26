// defines pins numbers
//Servo
#include<Servo.h>
Servo leftServo;
Servo rightServo;

//IR sensor
const int right=7;
const int ctr=6;
const int left=5;
long int left_ir, right_ir, center_ir, mid_l, mid_r, mid_c, low_l, high_l, low_r, high_r, high_c, low_c; //caliberation variables for IR

//Wheel parameters
int wheel_speed = 5;
const int buffer_speed = 0;

//Counters
unsigned int basic_counter = 0;
unsigned int main_counter = 0;
float obstacle_counter = 0;
float len_counter = 0;
unsigned int car_counter = 0;
unsigned int bike_counter = 0;

//define flags
int back_flag = 1;
bool ultra_flag = 0;
bool right_flag = 0;
bool left_flag = 0;
bool basic_flag = 1;

// defines variables
long duration;

double distance;
long duration_ultra;
int tDistance = 20;

// defines pins numbers
const int trigPin = 2;
const int echoPin = 3;

const int intersection_led = A0;
const int obstacle_led = A1;
// defines variables

void basic_line_follower(){
 ir_read();
 ultra();
  
 if ((basic_counter%7) == 1 && distance < tDistance){
   right_flag = 1;
   flash_led(obstacle_led,1);
 }
 
 else{
  flash_led(obstacle_led,0);
 }
 
 if ((basic_counter%7) == 4 && distance < tDistance){
   left_flag = 1;
   flash_led(obstacle_led,1);
 }
 else{
   flash_led(obstacle_led,0);
 }
 if (basic_counter%7 == 1 or basic_counter%7 == 4){
  len_counter++; 
    if (distance < tDistance ){
       obstacle_counter++;
    }
  }
   
 if (left_ir == 1 && right_ir == 1 && center_ir == 1){
   basic_counter++;
   basic_flag = 0; 
   Serial.println("setting basicflag to zero");
 }
 else if (center_ir == 1 && right_ir == 0 && left_ir == 0){
  //straight
  leftServo.write(90 - back_flag*wheel_speed);
  rightServo.write(90 + back_flag*wheel_speed);
  Serial.println("front");
 }
 else if (left_ir == 1){
  //turnleft
    leftServo.write(90 - back_flag*wheel_speed*2);
    rightServo.write(90 - back_flag*wheel_speed);    
    Serial.println("correction left");
 }
 else if (right_ir == 1){
  //turnleft
    leftServo.write(90 + back_flag*wheel_speed*2);
    rightServo.write(90 + back_flag*wheel_speed);    
    Serial.println("correction right");
 }
 else {     
  leftServo.write(90);
  rightServo.write(90);    
  Serial.println("stop");
 }
}

void drive(){
  //black = 1
  //white = 0
  if (basic_flag){
    basic_line_follower();
  }
  else if (basic_counter%7 == 1){
    flash_led(intersection_led,1);
    right_turn();
    leftServo.write(90 - back_flag*wheel_speed);
    rightServo.write(90 + back_flag*wheel_speed);
    Serial.println("front");
    delay(500);
    ultra_flag = 1;
    flash_led(intersection_led,0);
  }
   else if (basic_counter%7 == 2 && back_flag == 1){
    leftServo.write(90);
    rightServo.write(90);
    delay(500);
    if (float(obstacle_counter/len_counter) > 0.6 && obstacle_counter != 0){
      car_counter++;
      Serial.println("Car detected !! "+ String(float(obstacle_counter/len_counter)));      
    }
    
    else if (float(obstacle_counter/len_counter) < 0.6 && obstacle_counter != 0){
      bike_counter++;      
      Serial.println("Bike detected !!  "+ String(float(obstacle_counter/len_counter)));
    }
    else{
      Serial.println("No object ra venna !!");
    }
    u_turn();
    obstacle_counter = 0;
    len_counter = 0;
    basic_flag = 1;
    delay(500);
   }
  
  else if (basic_counter%7 == 3){
    if (!right_flag){
      right_turn();
      leftServo.write(90 - back_flag*wheel_speed);
      rightServo.write(90 + back_flag*wheel_speed);
      Serial.println("front");
      delay(500);
      basic_counter = 5;
    }
    else{
      leftServo.write(90 - back_flag*wheel_speed);
      rightServo.write(90 + back_flag*wheel_speed);
      Serial.println("continue forward ra deiii");
      delay(500);
      basic_flag = 1;
    }
  }
  
  else if (basic_counter%7 == 4){
    leftServo.write(90);
    rightServo.write(90);
    delay(500);
    u_turn();
    obstacle_counter = 0;
    len_counter = 0;
    basic_flag = 1;
    delay(500);
    ultra_flag = 1;
  }
  
  else if (basic_counter%7 == 5){
    if (float(obstacle_counter/len_counter) > 0.6 && obstacle_counter != 0){
      car_counter++;
      Serial.println("Car detected !!  "+ String(float(obstacle_counter/len_counter)));      
    }    
    else if (float(obstacle_counter/len_counter) < 0.6  && obstacle_counter != 0){
      bike_counter++;      
      Serial.println("Bike detected !!  "+ String(float(obstacle_counter/len_counter)));
    }
    else{
      Serial.println("No object ra venna !!");
    }
    left_turn();
    obstacle_counter = 0;
    len_counter = 0;
    leftServo.write(90 - back_flag*wheel_speed);
    rightServo.write(90 + back_flag*wheel_speed);
    Serial.println("left turn done");
    delay(500);
    ultra_flag = 0;
  }

  else if (basic_counter%7 == 6){
      basic_flag = 1;
      basic_counter = 0;
      leftServo.write(90);
      rightServo.write(90);
      Serial.println("1 segment sucessfully completed initiate stopping motors and resetting all periodic parameters");
      delay(2000);
      if (!right_flag){
        right_turn();
        leftServo.write(90 - back_flag*wheel_speed);
        rightServo.write(90 + back_flag*wheel_speed);
        Serial.println("front");
        delay(500);
        Serial.println("Acheived goal!!");
        ir_read();
        while(true)
        {
          basic_line_follower();
          Serial.println("Inside While loop");
          if (left_ir == 1 && right_ir == 1 && center_ir == 1){
             Serial.println("Acheived goal!!");
            basic_counter = 700; 
            basic_flag = 0;
            break;
           }
        }
        Serial.println("Acheived goal!!");
        basic_counter = 700;
        basic_flag = 0;
      }
      else if(!left_flag){
        left_turn();
        leftServo.write(90 - back_flag*wheel_speed);
        rightServo.write(90 + back_flag*wheel_speed);
        Serial.println("front");
        delay(500);
        ir_read();
        while(true)
        {
          basic_line_follower();
          Serial.println("Inside While loop");
          if (left_ir == 1 && right_ir == 1 && center_ir == 1){
             Serial.println("Acheived goal!!");
              basic_counter = 700;
              basic_flag = 0;
              break;
           }
        }
        Serial.println("Acheived goal!!");
        basic_counter = 700;
        basic_flag = 0;
      }
      else{
        leftServo.write(90 - back_flag*wheel_speed);
        rightServo.write(90 + back_flag*wheel_speed);
        Serial.println("front");
        delay(500);
        right_flag = 0;
        left_flag = 0;
      }
    ultra_flag = 0;
    flash_led(intersection_led,1);
  }

  else{
    leftServo.write(90);
    rightServo.write(90);
    Serial.println("Stop servos");
    delay(10000);
    }
}

int main_(){
  while(true){
    drive();
  }
}

void setup() {
  // put your setup code here, to run once:
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input

  pinMode(intersection_led,OUTPUT);
  pinMode(obstacle_led,OUTPUT);

  Serial.begin(9600);
 
  Serial.println("Entering into callibration");
  callibration();
  
  Serial.println("Out of callibration");
  delay(5000);
  
  leftServo.attach(9);
  rightServo.attach(10);
  main_();
}

void flash_led(int led_pin, int state)
{
  digitalWrite(led_pin,state);  
}

void loop() {
  // put your main code here, to run repeatedly:
  //Unakku oru velaiyum illa  
}
