#include "../include/main.h"
#include "liblvgl/llemu.hpp"
#include "pros/misc.h"
#include "pros/rtos.hpp"
#include <cstdint>
#include <numbers>

using namespace std;

pros::Controller trunk(CONTROLLER_MASTER);
pros::Controller branch(CONTROLLER_PARTNER);

bool CEN_BOOL = false;
bool ARM_BOOL = true;
bool DONKER_BOOL = false;

pros::adi::DigitalOut CEN('A', CEN_BOOL);
pros::adi::DigitalOut ARM('C', ARM_BOOL);
pros::adi::DigitalOut DONKER('B', DONKER_BOOL);

pros::MotorGroup MG_Left({10, -9, 8}, pros::v5::MotorGears::blue,
                         pros::v5::MotorUnits::degrees);
pros::MotorGroup MG_Right({-1, 2, -3}, pros::v5::MotorGears::blue,
                          pros::v5::MotorUnits::degrees);
pros::MotorGroup MG_Elr({-6, 5}, pros::v5::MotorGears::blue,
                        pros::v5::MotorUnits::degrees);

pros::Imu imu(4);

double wheel_die = 2.72;

int avg_pos() {
  int avg_left = MG_Left.get_position();
  int avg_right = MG_Right.get_position();
  int avg_imu = imu.get_heading();

  int avg = (avg_left + avg_right + avg_imu) / 2;

  return avg;
}

void drivef(double dist, std::int32_t velocity) {
  double r_dist = (dist / (numbers::pi * wheel_die) * 360) - 9;

  MG_Left.move_relative(r_dist, velocity);
  MG_Right.move_relative(r_dist, velocity);

  while (!(avg_pos() < r_dist + 5) && (avg_pos() > r_dist - 5)) {
    pros::delay(2);
  }
}

void spinf(double dist, std::int32_t velocity) {
  double r_dist = dist / (numbers::pi * wheel_die) * 360;

  MG_Left.move_relative(r_dist, velocity);
  MG_Right.move_relative(-r_dist, velocity);
}

void auton_one() {
  drivef(-55, 600);

  pros::delay(1000);

  CEN_BOOL = !CEN_BOOL;
  ARM_BOOL = !ARM_BOOL;

  CEN.set_value(CEN_BOOL);

  pros::delay(10);

  ARM.set_value(ARM_BOOL);

  pros::delay(50);

  MG_Elr.move(-127 * 0.8);
}

void auton_two() {
  drivef(-55, 1000);

  spinf(180, 600);
}

void auton_skills() {}

int auto_state = 0;

void button_one() {
  auto_state = 0;
}

void button_two() {
  auto_state = 1;
}

void button_three() {
  auto_state = 2;
}

void autonomous() {
  switch (auto_state) {
  case 0:
    auton_one();
  case 1:
    auton_two();
  case 2:
    auton_skills();
  }
}

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

    if (trunk.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2)) {
      DONKER_BOOL = !DONKER_BOOL;
      DONKER.set_value(DONKER_BOOL);
    }

    /*======================*
     *   BRANCH CONTROLES   *
     *======================*/

    if (branch.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1)) {
      ARM_BOOL = !ARM_BOOL;
      ARM.set_value(ARM_BOOL);
    }

    MG_Elr.move(branch.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y) * 0.8);

    pros::delay(20);
  }
}
