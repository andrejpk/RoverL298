#include <RoverL298.h>

// Set up the controller; 
// Pin mappings: EN_A, EN_B, IN_1, IN_2, IN_3, IN_4
RoverL298 rover(3,5,11,10,9,6);

void setup() {
   
  
}

void loop()
{
   // move forward at full speed, straight ahead
   rover.motorMove(100,0);
   delay(1000);  // keep going for one second
   rover.motorMove(-100,50); // back up turning right
   delay(1000);  // keep backing up for a one second
   
}