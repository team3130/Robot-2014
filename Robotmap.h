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

// Digital Input channels
#define C_PRESSURE_SWITCH 9
#define C_ENCODER_WINCH_CHANNEL_1  5
#define C_ENCODER_WINCH_CHANNEL_2  6
#define C_ENCODER_STOPPER_A 10
#define C_ENCODER_STOPPER_B 11
#define C_ENCODER_ARM_A 12
#define C_ENCODER_ARM_B 13
#define C_ENCODER_INTAKE_CHANNEL_1 7
#define C_ENCODER_INTAKE_CHANNEL_2 8
#define C_ENCODER_LEFT_A  3
#define C_ENCODER_LEFT_B  4
#define C_ENCODER_RIGHT_A 1
#define C_ENCODER_RIGHT_B 2

// Analog Input channels
#define C_GYRO 1

// Relays and solenoids
#define C_COMPRESSOR_RELAY 1
#define C_SHOOTERSOLENOID1 4
#define C_SHOOTERSOLENOID2 5
#define C_EXTENDSOLENOID1 6
#define C_IDLESOLENOID 3
#define C_SHIFTER 2

// Motors (Jag and Talons)
#define C_WINCHMOTOR1 3
#define C_STOPPERMOTOR 6
#define C_INTAKEMOTOR1 5
#define C_LEFTMOTOR 2
#define C_RIGHTMOTOR 1
#define C_LEFTSATELLITE 4
#define C_RIGHTSATELLITE 3

// Buttons
#define B_EXTENDARMS 4
#define B_PULLARMS 2
#define B_IDLEARMS 1
#define B_BEATERBAR 6
#define B_POWERWINCH 2
#define B_STOPPERWINCH 5
#define B_SHOOT 8
#define B_LOCKSHOOTER 3

// If you are using multiple modules, make sure to define both the port
// number and the module. For example you with a rangefinder:
// #define RANGE_FINDER_PORT 1
// #define RANGE_FINDER_MODULE 1

//#define C_SHIFTER_MODULE 1

#endif
