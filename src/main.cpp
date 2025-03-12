#include "../include/main.h"

using namespace std;

pros::Controller trunk(CONTROLLER_MASTER);
pros::Controller branch(CONTROLLER_PARTNER);

bool CEN_BOOL = false;
bool TRANS_BOOL = false;
bool DONK_BOOL = false;

pros::adi::DigitalOut TRANS('A', TRANS_BOOL);
pros::adi::DigitalOut CEN('B', CEN_BOOL);
pros::adi::DigitalOut DONK('C', DONK_BOOL);

pros::MotorGroup MG_Left({10, -9, 8}, pros::v5::MotorGears::blue,
                         pros::v5::MotorUnits::degrees);
pros::MotorGroup MG_Right({-1, 2, -3}, pros::v5::MotorGears::blue,
                          pros::v5::MotorUnits::degrees);
pros::Motor Elr(21, pros::v5::MotorGears::blue,
                        pros::v5::MotorUnits::degrees);
pros::MotorGroup MG_Lift({-5,6});

pros::Imu nimu(4);
pros::Imu rimu(-7);

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

    /*=======================*
     *   BRANCH CONTROLERS   *
     *=======================*/

    Elr.move(branch.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y) * 0.8);

    pros::delay(2);
  }
}
