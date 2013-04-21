/*
  RoverL298.cpp - - Motor control library for a rover using the L298 DC controller
  
  Original library     (0.1) by Andrej Kyselica
*/

// ensure this library description is only included once
#ifndef RoverL298_h
#define RoverL298_h


#define COMMAND_FORWARD 1
#define COMMAND_REVERSE 2
#define COMMAND_COAST 3
#define COMMAND_BRAKE 4
 
 
// library interface description
class RoverL298 {
  public:
    // constructors:
    RoverL298(int pin_ena, int pin_enb, int pin_in1, int pin_in2, int pin_in3, int pin_in4 );
   
    // speed setter method:
	void motorMove(int speed, int steering);

	// housekeeping
    int version(void);

  private:
    void motorCommandPercent(int motorNum, int percent);
    void motorCommand(int motorNum, int command, int movementSpeed);

    int pin_count;        

    // motor pin numbers:
    int pin_ena;
    int pin_enb;
    int pin_in1;
    int pin_in2;
    int pin_in3;
    int pin_in4;  
};

#endif

