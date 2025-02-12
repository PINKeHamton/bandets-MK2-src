#include "../include/main.h"
#include "liblvgl/llemu.hpp"
#include "pros/misc.h"
#include "pros/motors.h"
#include "pros/rtos.hpp"

using namespace std;

pros::Controller trunk(CONTROLLER_MASTER);
pros::Controller branch(CONTROLLER_PARTNER);

bool CEN_BOOL = true;
bool ARM_BOOL = true;

pros::adi::DigitalOut CEN('A', CEN_BOOL);
pros::adi::DigitalOut ARM('C', ARM_BOOL);

pros::MotorGroup MG_Left({10, -9, 8}, pros::v5::MotorGears::blue,
                         pros::v5::MotorUnits::degrees);
pros::MotorGroup MG_Right({-1, 2, -3}, pros::v5::MotorGears::blue,
                          pros::v5::MotorUnits::degrees);
pros::Motor Elr(21, pros::v5::MotorGears::blue,
                        pros::v5::MotorUnits::degrees);
pros::MotorGroup MG_ARM({-10,11}, pros::v5::MotorGears::blue,
                        pros::v5::MotorUnits::degrees);

pros::Imu nimu(4);
pros::Imu rimu(-7);

void opcontrol() {
  int right;
  int left;

  while (1) {

    /*======================*
     *   TRUNK CONTROLES    *
     *======================*/

    int linear = trunk.get_analog(ANALOG_LEFT_Y);
    int strafe = trunk.get_analog(ANALOG_RIGHT_X);
    right = linear;
    left = linear;

    if (linear == 0 && strafe > 0) {
      right += strafe;
      left -= strafe;
    } else if (linear == 0 && strafe < 0) {
      right += strafe;
      left -= strafe;
    } else if (strafe > 0) {
      right += strafe;
      left *= 0.8;
    } else if (strafe < 0) {
      left -= strafe;
      right *= 0.8;
    }

    MG_Left.move(left);
    MG_Right.move(right);

    if (trunk.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1)) {
      CEN_BOOL = !CEN_BOOL;
      CEN.set_value(CEN_BOOL);
    }

    /*======================*
     *   BRANCH CONTROLES   *
     *======================*/

    if (branch.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1)) {
      ARM_BOOL = !ARM_BOOL;
      ARM.set_value(ARM_BOOL);
    }

    int ARM_THING(branch.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y));

    MG_ARM.move(ARM_THING);
    MG_ARM.get_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

#define MAX_ARM_POS 100 

    if(MG_ARM.get_position() == MAX_ARM_POS){
      MG_ARM.get_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    }

    Elr.move(branch.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y) * 0.8);

    pros::delay(2);
  }
}
