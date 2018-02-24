#pragma config(Motor,  port1,           leftBack,      tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           leftTop,       tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           rightBack,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           mobileLift,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           leftWinch,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           rightWinch,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           claw,          tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           arm,           tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port10,          rightTop,      tmotorVex393_HBridge, openLoop)

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*        Description: Competition template for VEX EDR                      */
/*                                                                           */
/*---------------------------------------------------------------------------*/

// This code is for the VEX cortex platform
#pragma platform(VEX2)

// Select Download method as "competition"
#pragma competitionControl(Competition)

//Main competition background code...do not modify!
#include "Vex_Competition_Includes.c"

#define C1LX vexRT[Ch2]
#define C1LY vexRT[Ch1]
#define C1RX vexRT[Ch4]

#define FULLPWR 127
#define HALFPWR 63
#define QTRPWR 32

//int X2 = 0, Y1 = 0, X1 = 0, threshold = 15;
#define Y1 vexRT[Ch1]
#define X1 vexRT[Ch2]
#define X2 vexRT[Ch4]

void sideDrive(int drivespd_direction, int time)
{
	//this function drives to the left or the right at a chosen speed
	motor[rightTop] = drivespd_direction;
	motor[leftBack] = -drivespd_direction;
	wait1Msec(time); //1000 miliseconds is 1 second
}

void sideDriveGoal(int drivespd_direction, int time)
{
	//this function drives to the left or the right at a chosen speed
	motor[rightTop] = drivespd_direction - 48;
	motor[leftBack] = -drivespd_direction;
	wait1Msec(time); //1000 miliseconds is 1 second
	motor[rightTop] = 0;
	motor[leftBack] = 0;
}

void frontDrive(int drivespd_direction, int time)
{
	//this function drives forward of backward at a chosen speed
	motor[rightBack] = drivespd_direction;
	motor[leftTop] = -drivespd_direction;
	wait1Msec(time);
	motor[rightTop] = 0;
	motor[leftTop] = 0;
}

void turnNinetyNinety(int drivespd_direction, int time)
{
	motor[rightBack] = drivespd_direction - 10;
	motor[leftBack] = drivespd_direction;
	motor[rightTop] = drivespd_direction - 10;
	motor[leftTop] = drivespd_direction - 10;
	wait1Msec(time);
}

void winchWind (int spd)
{
	motor[leftWinch] = spd;
	motor[rightWinch] = -spd;
	wait1Msec(1000); //still have to find out how long it takes to lift the scissor lift
}

void mobileLiftUp (int spd, int time)
{
	motor[mobileLift] = spd;
	winchWind(spd);
	wait1Msec(time);

}

void armDown(int speed)
{
	motor[claw] = speed;
	wait1Msec(1000);
}

void clawOpen(int speed)
{
	motor [arm] = speed;
	wait1Msec(500);
}

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the cortex has been powered on and    */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton()
{
  // Set bStopTasksBetweenModes to false if you want to keep user created tasks
  // running between Autonomous and Driver controlled modes. You will need to
  // manage all user created tasks if set to false.
  bStopTasksBetweenModes = true;

	// Set bDisplayCompetitionStatusOnLcd to false if you don't want the LCD
	// used by the competition include file, for example, you might want
	// to display your team name on the LCD in this function.
	// bDisplayCompetitionStatusOnLcd = false;

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

task autonomous()
{
	//frontDrive(FULLPWR, 9000);
	//code to close the claw first thing
	mobileLiftUp(-FULLPWR,550);
	frontDrive(HALFPWR, 5500);
	mobileLiftUp(FULLPWR, 200);
	armDown(FULLPWR);
	clawOpen(-FULLPWR);

	frontDrive(-HALFPWR, 4000);
	// move diagonally for abt 2-3 sec
	sideDrive(HALFPWR, 4000);
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

task usercontrol()
{

  while (true)
  {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.
    //motor power levels range from -127 (full reverse) to 0 (stopped) to 127 (full power)

    //sets each of the wheel/chassis motors to a channel on the joystick
		motor[leftTop] =  -C1LX - C1RX;
		motor[leftBack] =  C1LY - C1RX;
		motor[rightBack] =  C1LX - C1RX;
		motor[rightTop] = -C1LY - C1RX;

		//claw moves one direction when button 7D pressed
		if (vexRT[Btn7D] == 1)
		{
			motor[claw] = HALFPWR; //motor forward for about half power
		}
		else if (vexRT[Btn7L] == 1)
	  {
		 motor[claw] = -HALFPWR; //claw moves in opposite direction when button 7L pressed
  	}
		else
		{
			motor [claw] = 0;
  	}

  	//arm moves one direction when button 6D pressed
		if (vexRT[Btn6D] == 1)
		{
				motor[arm] = -HALFPWR; //motor forward for about half power
		}
		else if (vexRT[Btn6U] == 1)
	  {
	  		motor[arm] = HALFPWR; //arm moves in opposite direction when button 6U pressed
  	}
		else
		{
			motor [arm] = 0;
  	}


  	//goal lift
  	if (vexRT [Btn5U] == 1)
    {
    	motor[mobileLift] = HALFPWR;
    }
    else if (vexRT[Btn5D] == 1)
    {
    	motor[mobileLift] = -HALFPWR;
		}
		else
		{
			motor[mobileLift] = 0;
		}


  	//controlls the winding up and unwinding of the winch
  	if (vexRT [Btn7U] == 1)
    {
    	motor[leftWinch] = HALFPWR;
    	motor[rightWinch] = -HALFPWR;
    }
    else if (vexRT[Btn7R] == 1)
    {
    	motor[leftWinch] = -QTRPWR;
    	motor[rightWinch] = QTRPWR;
		}
		else
		{
			motor[leftWinch] = 0;
			motor[rightWinch] = 0;
		}
  }
}
