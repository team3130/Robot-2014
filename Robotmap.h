/*-------------------------------------------------------------------------*/
/* Copyright (c) 2014 FRC-3130 "ERROR 3130". All Rights Reserved.          */
/* Open Source Software - may be modified, shared, used and reused by FRC  */
/* teams under the same license as the WPILib code itself.                 */
/* Authors: Ashwin Chetty                                                  */
/*-------------------------------------------------------------------------*/
#ifndef ROBOTMAP_H
#define ROBOTMAP_H


/**
 * The RobotMap is a mapping from the ports sensors and actuators are wired into
 * to a variable name. This provides flexibility changing wiring, makes checking
 * the wiring easier and significantly reduces the number of magic numbers
 * floating around.
 */
 
// For example to map the left and right motors, you could define the
// following variables to use with your drivetrain subsystem.

// It is convention to name all #defined constants with all caps names.

#define C_LEFTMOTOR 1
#define C_RIGHTMOTOR 2
#define C_WINCHMOTOR 3
#define C_STOPMOTOR 4
#define C_SHOOTERSOLENOID 5
#define C_INTAKEMOTOR 6
#define C_EXTENDSOLENOIDA 7
#define C_EXTENDSOLENOIDB 8
#define C_ENCODER_RIGHT_A 1
#define C_ENCODER_RIGHT_B 2
#define C_ENCODER_LEFT_A 3
#define C_ENCODER_LEFT_B 4
#define C_ENCODER_STOP_CHANNEL_A 5
#define C_ENCODER_STOP_CHANNEL_B 6
#define C_ENCODER_ARM_CHANNEL_A 7
#define C_ENCODER_ARM_CHANNEL_B 8
//#define C_ENCODER_INTAKE_CHANNEL_A 9
//#define C_ENCODER_INTAKE_CHANNEL_B 10
#define C_ENCODER_WINCH_CHANNEL_A 9
#define C_ENCODER_WINCH_CHANNEL_B 10 
#define C_GYRO 1

// If you are using multiple modules, make sure to define both the port
// number and the module. For example you with a rangefinder:
// #define RANGE_FINDER_PORT 1
// #define RANGE_FINDER_MODULE 1

#endif
