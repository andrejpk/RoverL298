RoverL298
=========

Arduino library for an L298-based two-motor rover.

This library adds simple wrappers for a two-motor rover based on the 
ST Micro L298 dual H-bridge driver. 

The included **SimpleDizzy** example shows the basic usage.

First, initialize the controller object. The parameters are the pin numbers of the EN_A, EN_B, IN_1, IN_2, IN_3, IN_4 pins respectively.  

	RoverL298 rover(3,5,11,10,9,6);

These values should match the wiring order of the Arduino to the L298 board.

After that's done, the rover can be controlled in the program using the motorMove function:

	rover.motorMove(speed, steering); 

Both parameters are integers from -100 to 100. The **speed** parameter determines the speed of the rover either going forward or in reverse: -100 goes full speed reverse and 100 goes full forward. The  **steering** parameter sets steering: 0 goes straight, -50 is a left turn, 50 is a right turn, -100 spins in place clockwise, 100 spins counterclockwise. Values between these work proportionally.  

The motorMove command starts the movement in the motor which will keep going until another command is received. To maintain movement for specific times use a **delay()** call or some other code that waits for something else to happen.

The steering and movement may need to be tweaked for straightness because of variations in motors and wheel specs. To get precise movement control, you need a rotary encoder or other way to measure the actual movement of the robot as it goes. This library doesn't handle this.

The RoverL298 library also provides lower-level access functions like **motorCommandPercent** and **motorCommand**. Look at the source code for the library to see how these work. The **motorMove** function calls these to control the motors. 