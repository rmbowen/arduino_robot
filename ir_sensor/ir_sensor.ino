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
  
  int irValue = readIR();
  
  // Read and output raw IR value
  Serial.print("IR (RAW): ");
  Serial.print(readIR());
  
  Serial.print("IR (Inches): ");
  Serial.println(convertIRInches(irValue));

  // Wait for new measurement
  delay(1000);
  
}

// read and return the raw ir value
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
