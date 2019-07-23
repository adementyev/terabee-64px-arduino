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
  pinMode(13, OUTPUT);              // Initialize digital pin 13 as an output (ERASABLE if the communication works)
  Serial.begin(0);             // Open serial port 0 (which corresponds to USB port and pins TX0 and RX0), set data rate to 115200 bps
  Serial1.begin(3000000);            // Open serial port 1 (which corresponds to pins TX1 and RX1), set data rate to 115200 bps
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
