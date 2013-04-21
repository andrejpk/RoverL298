/*
  RoverL298.cpp - - Motor control library for a rover using the L298 DC controller
  
  Original library     (0.1) by Andrej Kyselica
  
 */


#include "Arduino.h"
#include "RoverL298.h"

/*
 * the controller uses 6 control lines; each motor has enable and two data terminals
 */
RoverL298::RoverL298(int pin_ena, int pin_enb, int pin_in1, int pin_in2, int pin_in3, int pin_in4 )
{
  this->pin_ena = pin_ena;      // enable motor 0
  this->pin_enb = pin_enb;      // enable motor 1
  this->pin_in1 = pin_in1;      // enable motor 0 control 1
  this->pin_in2 = pin_in2;      // enable motor 0 control 2
  this->pin_in3 = pin_in3;      // enable motor 1 control 1
  this->pin_in4 = pin_in4;      // enable motor 1 control 2
  
  // setup the pins on the microcontroller:
  pinMode(this->pin_ena, OUTPUT);
  pinMode(this->pin_enb, OUTPUT);
  pinMode(this->pin_in1, OUTPUT);
  pinMode(this->pin_in2, OUTPUT);
  pinMode(this->pin_in3, OUTPUT);
  pinMode(this->pin_in4, OUTPUT);

  digitalWrite(this->pin_ena, LOW);
  digitalWrite(this->pin_enb, LOW);
  digitalWrite(this->pin_in1, LOW);
  digitalWrite(this->pin_in2, LOW);
  digitalWrite(this->pin_in3, LOW);
  digitalWrite(this->pin_in4, LOW);
  
  // pin_count is used by the stepMotor() method:
  this->pin_count = 6;
}


/*
 *  speed: -100 to 100; steering: -100 to 100
 *    at 100, 0, both motors max forward
 *    at -100, 0, both motors max reverse
 *    at 100, -50, left motor = 0, right motor = max forward
 *    at 100, -100, left motor = max reverse, right motor = max forward
 *    at 100, -25, left motor = 50%, right motor = max forward
 */
void RoverL298::motorMove(int speed, int steering)
{
  int leftPercent = max(min(speed*((steering*2)+100)/100,100),-100);
  int rightPercent = max(min(speed*((steering*-2)+100)/100,100),-100);
  
  // Serial.print("movement: ");
  // Serial.print(speed);
  // Serial.print(",");
  // Serial.print(steering);
  // Serial.print(" -> ");
  // Serial.print(leftPercent);
  // Serial.print(",");
  // Serial.println(rightPercent);
  
  this->motorCommandPercent(1, leftPercent);
  this->motorCommandPercent(2, rightPercent);
}


void RoverL298::motorCommandPercent(int motorNum, int percent)
{
  if (percent == 0)
  {
    motorCommand(motorNum, COMMAND_BRAKE, 255);
        // Serial.print("motor brake ");
    // Serial.println(motorNum);
  }
  else if (percent < 0)
  {
    motorCommand(motorNum, COMMAND_REVERSE, (percent * 1.55) + 100);
    // Serial.print("motor RV: ");
    // Serial.print(motorNum);
    // Serial.print(" @ ");
    // Serial.println((percent * 1.55) + 100);
    
  }
  else 
  {
    motorCommand(motorNum, COMMAND_FORWARD, (percent * 1.55) + 100);
    // Serial.print("motor FW: ");
    // Serial.print(motorNum);
    // Serial.print(" @ ");
    // Serial.println((percent * 1.55) + 100);
  }
}

/*
 * primarily used internally for low-level motor control
 */
void RoverL298::motorCommand(int motorNum, int command, int movementSpeed)
{
  int en, ina, inb;
  if (motorNum == 1)
  {
    en = this->pin_ena;
    ina = this->pin_in1;
    inb = this->pin_in2;
  }
  else
  {
    en = this->pin_enb;
    ina = this->pin_in3;
    inb = this->pin_in4;
  }

  analogWrite(en, movementSpeed);
  if (command == COMMAND_FORWARD)
  {
    digitalWrite(ina, HIGH);
    digitalWrite(inb, LOW);
  }
  else if (command == COMMAND_REVERSE)
  {
    digitalWrite(ina, LOW);
    digitalWrite(inb, HIGH);
  }
  else if (command == COMMAND_COAST)
  {
    digitalWrite(ina, LOW);
    digitalWrite(inb, LOW);
  }
  else if (command == COMMAND_BRAKE)
  {
    digitalWrite(ina, HIGH);
    digitalWrite(inb, HIGH);
  }
}

/*
  version() returns the version of the library:
*/
int RoverL298::version(void)
{
  return 1;
}
