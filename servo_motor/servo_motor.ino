/* FileName: servo_motor
 * 
 * Author: Ryan M. Bowen
 * Email:  rmb3518@gmail.com
 *
 * Description: Provides functionality to move a micro-servo.
 *              Uses a timer to pan the servo.
 *              Design for use in RoboCamp - Expert @ RIT
 *
 *
 * Date Modified: 08/06/2013
 *
 * PIN_OUT:
 *            5 ---> Servo PWM
 *
 * Hardware:  DFRobot Micro Servo Motor
 */

#define SERVO   5  // Servo Motor Pin


// Servo PWM values
#define SERVO_LOWER    500
#define SERVO_MID      1500
#define SERVO_UPPER    2600
#define SERVO_PAN_STEP 20 

// Counter used in timer interrupt
int counter;

// Number of overflows for pan
int flowCount = 10;

// Direction of the servo
boolean servoDir;

// PWM value for the Servo
int servoValue;

/**
 *  setup - Setup pin modes, variables and set servo 
 **/
void setup() {
  // Setup servo pin for output
  pinMode(SERVO,OUTPUT);
  
  // Reset the counter for timer overflows
  counter = 0;
  
  // Set the servoValue to the mid-value
  servoValue = SERVO_MID;
  
  // Move the servo to the center position 
  // Using a loop here to ensure the servo 
  // has ample time to get to the center
  for(int i=0; i<30; i++)
  {
     writeServo(servoValue);
     delay(20); 
  }
  
  // Setup the Timer for panning
  setupPanningTimer();
  
  // Turn on the Timer for panning
  turnOnServoPan();
  
}

/**
 * Main looped code
 **/
void loop() {
  // NONE Here, only panning using timer interrupts
}

/** 
 * writeServo - Creates the PWM pulse to move the servo.
 *              Needs to be called repeatedly ~10x every 20us or more
 *                
 * @param pulseWidth - integer value of the PWM ON-Time Width 
 */
void writeServo(int pulseWidth)
{
  
  // Set pulse High
  digitalWrite(SERVO, HIGH);
  
  // Wait for ON-Time width
  delayMicroseconds(constrain(pulseWidth, SERVO_LOWER, SERVO_UPPER) );
  
  // Bring pulse low
  digitalWrite(SERVO, LOW);
  
}

/** 
 * setupPanningTimer - Sets a timer to be used to pan a servo
 **/ 
void setupPanningTimer()
{
  // Setup the Timer Interrupt
  
  // Timer2 - PreScalar 1024
  TCCR2A |= ( (1<<CS22) | (0<<CS21) | (1<<CS20) );
  
  // Normal Mode
  TCCR2A |= (0<<WGM21) | (0<<WGM20);
  
  // Use internal clock - external clock not used in Arduino
  ASSR   |= (0<<AS2);
  
  // Enable Timer2 Overflow Interrupt Enable
  // TIMSK2 |= (1<<TOIE2) | (0>>OCIE2A);
 
  // Reset the bottom value of the timer 
  TCNT2 = 6;
  
}

/**
 * Start Panning by turning on Timer2
 **/
void turnOnServoPan()
{
   TIMSK2 |= (1<<TOIE2); 
}

/**
 * Stop Panning by turning off Timer2
 */
void turnOffServoPan()
{
   TIMSK2 &= ~(1<<TOIE2); 
}

/**
 * Interrupt Subroutine for Timer2 Overflow 
 **/
ISR(TIMER2_OVF_vect)
{
  
  // Reset the timer 6 used for precision adjustment
  TCNT2 = 6;
  
  // Increment the counter
  counter += 1;
  
  // Check for desired number of overflows
  if( counter == flowCount ) {
    
      // Check the direction and continue in previous
      if( servoDir == false ){
         // Pan in same direction unless bound is hit, then reverse direction
         if( servoValue > SERVO_LOWER ){
           servoValue -= SERVO_PAN_STEP;
         }else{
           servoDir = true; 
         }
      }else{
         //  Pan in same direction unless bound is hit, then reverse
         if( servoValue < SERVO_UPPER ){
           servoValue += SERVO_PAN_STEP;
         }else{
           servoDir = false; 
         }
      }

      // Write the new value for the servo
      writeServo(servoValue);
  
      // Clear the counter    
      counter = 0;  
  }
  
} 
