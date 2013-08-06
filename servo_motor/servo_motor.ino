#include <avr/interrupt.h>
#include <avr/io.h>

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

void setup() {
  // Setup servo pin for output
  pinMode(SERVO,OUTPUT);
  
  // Setup the Timer for Panning
  setupPanningTimer();
  
  counter = 0;
  
  servoValue = SERVO_MID;
  
  turnOnServoPan();
  
}

void loop() {
  // put your main code here, to run repeatedly: 
  
}

void writeServo(int pulseWidth)
{
  
  // Set pulse High
  digitalWrite(SERVO, HIGH);
  
  // Wait for ON-Time width
  delayMicroseconds(constrain(pulseWidth, SERVO_LOWER, SERVO_UPPER) );
  
  // Bring pulse low
  digitalWrite(SERVO, LOW);
  
}

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

void turnOnServoPan()
{
   TIMSK2 |= (1<<TOIE2); 
}

void turnOffServoPan()
{
   TIMSK2 &= ~(1<<TOIE2); 
}

ISR(TIMER2_OVF_vect)
{
  // Reset the timer 
  TCNT2 = 6;
  
  // Increment the counter
  counter += 1;
  
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
