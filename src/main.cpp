#include "../include/main.h"
#include "pros/misc.h"
#include "pros/rotation.hpp"

using namespace std;

pros::Controller trunk(CONTROLLER_MASTER);
pros::Controller branch(CONTROLLER_PARTNER);

bool CEN_BOOL = false;
bool DONK_BOOL = false;

pros::adi::DigitalOut CEN('A', CEN_BOOL);
pros::adi::DigitalOut DONK('B', DONK_BOOL);

pros::MotorGroup MG_Left({10, -9, 8}, pros::v5::MotorGears::blue,
                         pros::v5::MotorUnits::degrees);
pros::MotorGroup MG_Right({-1, 2, -3}, pros::v5::MotorGears::blue,
                          pros::v5::MotorUnits::degrees);
pros::Motor Elr(5, pros::v5::MotorGears::blue,
                        pros::v5::MotorUnits::degrees);
pros::Motor LB(6, pros::v5::MotorGears::blue,
                        pros::v5::MotorUnits::degrees);

pros::Imu nimu(16);
pros::Imu rimu(-17);

pros::Rotation LBR(4);

void opcontrol() {
  int right;
  int left;

  while (1) {

    /*=======================*
     *   TRUNK CONTROLERS    *
     *=======================*/

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

    if (trunk.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)) {
      DONK_BOOL = !DONK_BOOL;
      DONK.set_value(DONK_BOOL);
    }
    
    bool setoff = false;
    
    if (trunk.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2)) {
      LB.move_relative(10, 200);
      if (LBR.get_angle() == 25) {
        LB.brake();
      }
    }
      
    

    /*=======================*
     *   BRANCH CONTROLERS   *
     *=======================*/

    Elr.move(branch.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y) * 0.8);

    pros::delay(2);
  }
}
