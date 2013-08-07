/* FileName: motors.ino
 * 
 * Author: Ryan M. Bowen
 * Email:  rmb3518@gmail.com
 *
 * Description: Simple DC motor control using Arduino Motor Shield V3
 *              Intended for use in RoboCamp - Expert @ RIT
 *
 * Date Modified: 08/07/2013
 *
 * PIN_OUT:
 *            PWM_RIGHT   --> 3
 *            PWM_LEFT    --> 11  
 *            DIR_RIGHT   --> 12 
 *            DIR_LEFT    --> 13  
 *            BRAKE_RIGHT --> 9   
 *            BRAKE_LEFT  --> 8 
 *        
 *
 * Hardware: (2) DC Motors, Arduino Motor Shield V3
 */
 
// Motor Sheild Pinouts
#define PWM_RIGHT    3   // Right Motor Speed
#define PWM_LEFT     11  // Left Motor Speed
#define DIR_RIGHT    12  // Right Motor Direction
#define DIR_LEFT     13  // Left Motor Direction
#define BRAKE_RIGHT  9   // Right Motor Brake 
#define BRAKE_LEFT   8   // Left Motor Brake

// Logic Switch Pin
#define LOGIC_SWITCH 4

// Motor Directions
#define RIGHT_MOTOR_FWD  LOW
#define RIGHT_MOTOR_REV  HIGH
#define LEFT_MOTOR_FWD   HIGH
#define LEFT_MOTOR_REV   LOW

// Stores value of logic switch
int logicSwitch = 0;

/**
 * Setup the motor shield pins
 */
void setup() {
  
  // Setup Z Motors
  pinMode(PWM_RIGHT, OUTPUT);
  pinMode(PWM_LEFT,  OUTPUT);
  pinMode(DIR_RIGHT, OUTPUT);
  pinMode(DIR_LEFT,  OUTPUT);
  pinMode(BRAKE_RIGHT, OUTPUT);
  pinMode(BRAKE_LEFT,  OUTPUT);
}

/** 
 *  Loop forward movement while logic switch is enabled
 */
void loop() {
 
  // Read/Store the value of the logic switch
  logicSwitch = digitalRead(LOGIC_SWITCH);
  
  // Check if logic switch is on (ON=LOW)
  if( logicSwitch == LOW ){
    
    // Go forward 128 (max speed)
    forward(128);  
    
  }else{
  
     // Logic switch is off stop the motors
     stop();
     delay(250); 
  }
  
}

/**
 *  Set the robot to go forward
 *
 *  @params speed - speed of the motors [0,128]
 */
void forward(int speed){
  
  // Be sure that the brake is off
  digitalWrite(BRAKE_RIGHT,LOW);
  digitalWrite(BRAKE_LEFT,LOW); 
   
  // Set the motor directions
  digitalWrite(DIR_RIGHT,RIGHT_MOTOR_FWD);
  digitalWrite(DIR_LEFT, LEFT_MOTOR_REV);
  
  // Set the speed of the motors
  analogWrite(PWM_RIGHT, speed);
  analogWrite(PWM_LEFT,  speed);
  
}

/**
 *  Stop the robot by applying the brakes
 */
void stop()
{
   // Turn on the brakes
   brakesOn();
}

/**
 * Move robot backwards
 *
 * @params speed - speed to move backwards [0,128]
 */
void backward(int speed) {
  
  // Be sure to turn off the brakes
  brakesOff();
  
  //Set direction
  digitalWrite(DIR_RIGHT, RIGHT_MOTOR_REV);
  digitalWrite(DIR_LEFT, LEFT_MOTOR_FWD);
  
  //Set speed
  analogWrite(PWM_RIGHT, speed);
  analogWrite(PWM_LEFT, speed);
}

/**
 * Rotate robot counter clockwise
 *
 * @params speed - speed to rotate [0,128]
 */
void rotateLeft(int speed) {
  
  // Be sure to turn off the brakes
  brakesOff();
  
  //Set Direction
  digitalWrite(DIR_RIGHT, RIGHT_MOTOR_FWD);
  digitalWrite(DIR_LEFT, LEFT_MOTOR_FWD);
  
  //Set speed
  analogWrite(PWM_RIGHT, speed);
  analogWrite(PWM_LEFT, speed);
}

/**
 * Rotate robot clockwise
 *
 * @params speed - speed to rotate [0,128]
 */
void rotateRight(int speed) {
  
  // Be sure to turn off the brakes
  brakesOff();
  
  //Set Direction
  digitalWrite(DIR_RIGHT, RIGHT_MOTOR_REV);
  digitalWrite(DIR_LEFT, LEFT_MOTOR_REV);
  
  //Set speed
  analogWrite(PWM_RIGHT, speed);
  analogWrite(PWM_LEFT, speed);
}

void brakesOn()
{
   //Turn on brakes
  digitalWrite(BRAKE_RIGHT,HIGH);
  digitalWrite(BRAKE_LEFT,HIGH);
}

void brakesOff()
{
    //Turn off brakes
  digitalWrite(BRAKE_RIGHT,LOW);
  digitalWrite(BRAKE_LEFT,LOW);
  
}
