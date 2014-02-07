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
#define C_ENCODER_LEFT_A 3
#define C_ENCODER_LEFT_B 4
#define C_ENCODER_RIGHT_A 1
#define C_ENCODER_RIGHT_B 2
#define C_GYRO 1

// If you are using multiple modules, make sure to define both the port
// number and the module. For example you with a rangefinder:
// #define RANGE_FINDER_PORT 1
// #define RANGE_FINDER_MODULE 1

#endif
