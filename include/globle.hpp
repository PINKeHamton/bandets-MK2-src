#include "auton.hpp"
#include "main.h"
#include "pros/rotation.hpp"

#ifndef _GLOBLE_H_
#define _GLOBLE_H


void auton_one(void);
void auton_two(void);
void auton_three(void);

extern pros::MotorGroup MG_Left;
extern pros::MotorGroup MG_Right;
extern pros::Motor Elr;
extern pros::adi::DigitalOut CEN;
extern pros::adi::DigitalOut ARM;

extern pros::Imu rimu;
extern pros::Imu nimu;

extern pros::Rotation LBR;

extern bool CEN_BOOL;
extern bool DONK_BOOL;

#endif 
