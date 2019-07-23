
import processing.serial.*;

Serial myPort;        // The serial port 

int ARRAY_SIZE = 64;
int [] rawDistanceArray = new int [ARRAY_SIZE]; 
int [] ambientArray= new int [ARRAY_SIZE];


void setup()
{
   size(displayWidth, 950, P3D); // animation is much smoother in P2D; text looks better with JAVA2D

   background(5);
      //Find serial port
    for (int i=0; i<Serial.list().length; i++) { 
      System.out.println(i + " : " + Serial.list()[i]); 
    }//end for
    
    System.out.println("ok");
    myPort = new Serial(this, Serial.list()[1], 1000000);
    frameRate(120);

    for (int i = 0; i < rawDistanceArray.length; i++) {
        rawDistanceArray[i] =0;
    }
    
    for (int i = 0; i < ambientArray.length; i++) {
        ambientArray[i] =0;
    }
 
}

void draw() { 
    
    //visualize pixel grid
    for( int g=0; g<8; g++ ){
      for( int i=0; i<8; i++ ){
        float colorMap = map(rawDistanceArray[i+g*8], 0.0 ,4000.0,  0.0,255.0);
        fill(colorMap);
        rect(50*i,50*g,50,50);
      }//end for
    }
    
    //visualize pixel grid for ambient array
    for( int g=0; g<8; g++ ){
      for( int i=0; i<8; i++ ){
        float colorMap = map(ambientArray[i+g*8], 0.0 ,20000.0,  0.0,255.0);
        fill(colorMap);
        rect(500+50*i,50*g,50,50);     
      }//end for
    }
    
  
}


public void serialEvent (Serial myPort) {
     try {     //Use try, catch to avoid crashing
       // get the ASCII string:
       String inString = myPort.readStringUntil('\n');        
       if (inString !=null ){
              inString = trim(inString);
             // System.out.println(inString);
              //System.out.println(inString.length());
       }
         
       if (inString != null && inString.length()>0 && inString.charAt(0) == 'E' ) {
       // trim off any whitespace:             
            inString = trim(inString);
            String[] list = split(inString, ',');
            
            ///rawDistanceArray[0] = Integer.parseInt(list[1]);
            for (int i=0; i<64; i++) {
              rawDistanceArray[i] = Integer.parseInt(list[i+1]);
            }
            
            for (int i=0; i<64; i++) {
              ambientArray[i] = Integer.parseInt(list[i+1+64]);
            }
       }               
      } catch (Exception e){ 
        System.out.println("ErrorSerial: " + e);
      }  
}//end SerialEvent



  
  
