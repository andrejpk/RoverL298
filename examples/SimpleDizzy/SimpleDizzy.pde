#include <RoverL298.h>

RoverL298 rover(3,5,11,10,9,6);

void setup() {
   
  
}

void loop()
{
   rover.motorMove(100,0);
   delay(1000);
   rover.motorMove(-100,50);
   delay(1000);
   
}