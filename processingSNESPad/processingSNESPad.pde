import processing.serial.*;

PFont font;
PFont fontSmall;
Robot r;
Serial myPort;

// CONFIGURE NOTE FOR EACH BUTTON
String[] button_code = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B"};
// ascii codes for the keypress.  check documentation
int[] keyPress_map = {80,81,  82,83,  84,85,  86,87,  88,89,  78,79};

// handle button state to stop multiple pressing
int[] keyState = {0,0,0,0,0,0,0,0,0,0,0,0};

void setup(){
  size(200, 150);

  // List all the available serial ports
  println(Serial.list());
  // Open the first port available
  myPort = new Serial(this, Serial.list()[0], 57600);
  // don't generate a serialEvent() unless you get a newline character:
  myPort.bufferUntil('\n');
 
 // create 'robot' for keypresses
 try{
    r = new Robot();
  } catch(AWTException a){}
 
 // draw the window
 background(53);
 
 // initialize font
 font = loadFont("Tahoma.vlw");
 fontSmall = loadFont("Tahoma-small.vlw");
  
 // write in the box
 textFont(font); 
 text("SNESpad", 35, 130);
 textFont(fontSmall);
 text("by: Edmundo Fuentes", 95, 143);  
}

void draw() {
}

void serialEvent(Serial myPort){
  String inString = myPort.readStringUntil('\n');
  
  if (inString != null) {
    // trim off any whitespace:
    inString = trim(inString);
    
    for(int n=0; n<=11; n++){
      String button = button_code[n];
      if(inString.indexOf(button) >= 0){
        // The code is in there, execute the action
        // check the button last state
        if(keyState[n] == 0){
          r.keyPress(keyPress_map[n]);
          keyState[n] = 1;
        }  
      } else { 
        if(keyState[n] == 1){
          r.keyRelease(keyPress_map[n]);
          keyState[n] = 0;
        }
      } 
    }   
   
   // delay to see the result
  // delay(200); 
  }
  
}


