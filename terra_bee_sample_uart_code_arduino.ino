/**
 * Minimum code to send data from terabee 64 pixel sensor from arduino (Teensy 3.6) to a computer
 */

uint8_t distanceFrame [256];
uint8_t ambientFrame  [128];
//uint8_t distance
int indexDistance =0 ; 
bool startDistance = false;
uint16_t distance [128];               


uint8_t prev_inChar; 
 

void setup() {
  Serial.begin(0);             // Open serial port for USB serrial
  Serial1.begin(3000000);            // Open serial port 1
}


// The main loop starts here
void loop() {
  if (Serial1.available() > 0) {                          // Send data only when you receive data  
    uint8_t inChar = Serial1.read();                        // Read the incoming byte and save it in the variable "inChar"
    if (inChar ==0x11) { 
       Serial1.readBytes(distanceFrame,256);
       for(int i=0; i<128; i++) {
          distanceFrame[i*2] &= ~(1UL << 7);
          distanceFrame[(i*2)+1] &= ~(1UL << 7);
          distance[i] = (distanceFrame[i*2]<<8) + distanceFrame[(i*2)+1]; 
       }

       Serial.print("E");
       Serial.print(",");
       for(int i=0; i<128; i++) { 
          Serial.print(distance[i]);
          Serial.print(",");
       }
       Serial.println("");           
    }//end if char 0x11
  }
}
