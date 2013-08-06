// IR Pin
#define IR   A2

void setup() {

    // Setup the Serial Port
    Serial.begin(9600);
    
    // Set the IR for Input
    pinMode(IR, INPUT);
    
}

void loop() {
  
  int irValue;
  
  // Use function to read raw IR value
  irValue = readIR();
  
  // Output the value to the monitor
  Serial.println("IR (RAW): " + irValue );
  
  // Wait for new measurement
  delay(1000);
  
}

int readIR()
{
   // read and return the raw ir value
   return analogRead(IR); 
}
