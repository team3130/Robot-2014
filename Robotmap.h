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
#define C_PRESSURE_SWITCH 14 
#define C_ENCODER_WINCH_CHANNEL_1  9
#define C_ENCODER_WINCH_CHANNEL_2  10
#define C_ENCODER_STOPPER_A 5
#define C_ENCODER_STOPPER_B 6
#define C_ENCODER_CATAPULT_A 10
#define C_ENCODER_CATAPULT_B 11
#define C_ENCODER_LEFT_A  3
#define C_ENCODER_LEFT_B  4
#define C_ENCODER_RIGHT_A 1
#define C_ENCODER_RIGHT_B 2
#define C_ARM_SWITCH 13

#define C_WINCH_TAUT 12

// Analog Input channels
#define C_GYRO 1

// Relays
#define C_COMPRESSOR_RELAY 1

// Solenoids
#define C_SHOOTERSOLENOID1 4
#define C_SHOOTERSOLENOID2 5
#define C_EXTENDSOLENOID1 2
#define C_IDLESOLENOID 1
#define C_SHIFTER 3

// PWM Motors (Jag and Talons)
#define C_WINCHMOTOR1 7
#define C_STOPPERMOTOR 6	
#define C_INTAKEMOTOR1 5	//positive is INTAKE direction.
#define C_LEFTMOTOR 1
#define C_RIGHTMOTOR 3
#define C_LEFTSATELLITE 2
#define C_RIGHTSATELLITE 4

// Buttons and axis
#define B_HIGHGEAR 3
#define B_EXTENDARMS 5
#define B_IDLEARMS 10
#define A_BEATERBAR 3
#define B_BEATERBARFWD 2
#define B_BEATERBARREV 4
#define B_POWERWINCH 2
#define B_STOPPERWINCH 4
#define B_SHOOT 6
#define B_LOCKSHOOTER 9

// If you are using multiple modules, make sure to define both the port
// number and the module. For example you with a rangefinder:
// #define RANGE_FINDER_PORT 1
// #define RANGE_FINDER_MODULE 1

//#define C_SHIFTER_MODULE 1

// Geometry
#define N_WHEEL_DIAMETER 4.125
#define N_ENCODER_PPR 256
#define N_CHAIN_RATIO (28.0/22.0)
#define N_WHEEL_ENCODER_RATIO ((36.0/12.0)/N_CHAIN_RATIO)
#define N_FRAME_L 28.5
#define N_FRAME_H 13.75
#define N_FRAME_ARMLENGTH 23.0
#endif
