/* FileName: ir_sensor
 * 
 * Author: Ryan M. Bowen
 * Email:  rmb3518@gmail.com
 *
 * Description: Reads and converts analog IR sensor values.
 *              Designed for use in RoboCamp - Expert @ RIT 
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

void setup() {

    // Setup the Serial Port
    Serial.begin(9600);
    
    // Set the IR for Input
    pinMode(IR, INPUT);
    
}

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

// Read and return the raw ir value
int readIR()
{
   return analogRead(IR); 
}

// Read new IR value and return inches conversion
double readIRInches()
{
  return convertIRInches(readIR());   
}

// Return power curve conversion from raw IR value to inches
double convertIRInches(int rawValue)
{
     // change a and b to fit your sensor
     return a*pow(rawValue,b); 
}
