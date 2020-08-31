
// intended to augment the 4 buttons on a windows mouse
// Expects to use a leondardo/pro micro interface to be able to control the mouse

// Uses the arduino pullup resister on the pins to detect state. 
// So when a button is clicked, it is actually shorting to ground, or in a LOW state
// If the button is not pressed, it normally reads in the HIGH state
//

#include "Mouse.h"

// Declare the pins;
int LED = 13;
int mouseLeftButton = 7;
int mouseRightButton = 9; 
int mouseWheelUp = 16;
int mouseWheelDown = 8;

// variabled to read the button pin states
int mouseLeftState=0;
int mouseRightState=0;
int mouseWheelUpState=0;
int mouseWheelDownState=0;

int debug=0;

void setup() {
   // Initialize the buttons for use
   pinMode(mouseLeftButton, INPUT_PULLUP);
   pinMode(mouseRightButton, INPUT_PULLUP);
   pinMode(mouseWheelUp, INPUT_PULLUP);
   pinMode(mouseWheelDown, INPUT_PULLUP);
   

   // Initialize the various devices
   Serial.begin(9600);
   Mouse.begin();
   
   Serial.write("Initializing...\n");
   delay(1000);
   Serial.write("Done\n");
   delay(1000);   
}

void loop(){
   // check the state of the buttons, default is off
   mouseLeftState=      digitalRead(mouseLeftButton);
   mouseRightState=     digitalRead(mouseRightButton);
   mouseWheelUpState=   digitalRead(mouseWheelUp);
   mouseWheelDownState= digitalRead(mouseWheelDown);

   if(mouseLeftState == LOW){
     if (debug) {
       Serial.write("on  "); 
     }
     if (!Mouse.isPressed(MOUSE_LEFT)) {
       Mouse.press(MOUSE_LEFT);
     }
   } else {
     if (debug) {
       Serial.write("off "); 
     }
     if (Mouse.isPressed(MOUSE_LEFT)) {
       Mouse.release(MOUSE_LEFT);
     }
   }

   if(mouseRightState == LOW){
     if (debug) {
      Serial.write("on  "); 
     }
     if (!Mouse.isPressed(MOUSE_RIGHT)) {
       Mouse.press(MOUSE_RIGHT);
     }
   } else {
     if (debug) {
       Serial.write("off ");
     }
     if (Mouse.isPressed(MOUSE_RIGHT)) {
       Mouse.release(MOUSE_RIGHT);
     }
   }

   if(mouseWheelUpState == LOW){
     if (debug) {
      Serial.write("on  ");
     }
     Mouse.move(0,0,2);
   } else {
     if (debug) {
      Serial.write("off ");
     }
   }
   if(mouseWheelDownState == LOW){
     if (debug) {
      Serial.write("on  ");
     }
     Mouse.move(0,0,-2);
   } else {
     if (debug) {
      Serial.write("off ");
     }
   }

   if (debug) {
    Serial.write("\n");
   }

   // While debugging, set to something like 250
   // When not debugging, set to something like 100-50
   // it does not need to be checking the state that tight of a loop
   // also helps to prevent bounces (quick on/off/on/off as the button is being pressed or released)
   delay(100);
}
