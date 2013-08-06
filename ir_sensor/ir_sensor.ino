/* FileName: ir_sensor
 * 
 * Author: Ryan M. Bowen
 * Email:  rmb3518@gmail.com
 *
 * Description: Reads and converts analog IR sensor values.
 *              Designed for use in RoboCamp - Expert @ RIT 
 *
 * Date Modified: 08/06/2013
 *
 * PIN_OUT:
 *            A2 <--- IR
 *
 * Hardware: Sharp IR GP2Y0A21
 */
 
// IR Pin
#define IR   A2

// IR sensor power curve coefficients
// Change to match measured values
double a = 7408.3;
double b = -1.204;

/**
 * setup - setup pin modes and serial port
 */
void setup() {

    // Setup the Serial Port
    Serial.begin(9600);
    
    // Set the IR for Input
    pinMode(IR, INPUT);
    
}

/**
 * Main loop read and output IR values
 */
void loop() {
 
  // Read a new IR value 
  int irValue = readIR();
  
  // Output raw IR value
  Serial.print("IR (RAW): ");
  Serial.print(irValue);
  
  // Output the converted value (inches) 
  Serial.print("IR (Inches): ");
  Serial.println(convertIRInches(irValue));

  // Delay for output
  delay(1000);
  
}

/**
 * readIR - Read and return the raw IR value
 * 
 * @returns - IR Value in raw ADC value
 */
int readIR()
{
   return analogRead(IR); 
}

/**
 * readIRInches - Reads and return the converted IR value
 * 
 * @returns - IR Value in inches
 */
double readIRInches()
{
  return convertIRInches(readIR());   
}

/**
 * convertIRInches - Converts raw IR ADC value to inches
 * 
 * @returns - Converted raw ADC value to inches
 */
double convertIRInches(int rawValue)
{
     // change a and b to fit your sensor
     return a*pow(rawValue,b); 
}
