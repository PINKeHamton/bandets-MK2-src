#include "../include/main.h"
#include "liblvgl/llemu.hpp"
#include "pros/misc.h"
#include "pros/motors.h"
#include "pros/rtos.hpp"
#include <cstdint>
#include <numbers>

using namespace std;

pros::Controller trunk(CONTROLLER_MASTER);
pros::Controller branch(CONTROLLER_PARTNER);

bool CEN_BOOL = false;
bool ARM_BOOL = true;

pros::adi::DigitalOut CEN('A', CEN_BOOL);
pros::adi::DigitalOut ARM('C', ARM_BOOL);

pros::MotorGroup MG_Left({10, -9, 8}, pros::v5::MotorGears::blue,
                         pros::v5::MotorUnits::degrees);
pros::MotorGroup MG_Right({-1, 2, -3}, pros::v5::MotorGears::blue,
                          pros::v5::MotorUnits::degrees);
pros::Motor Elr(5, pros::v5::MotorGears::blue,
                        pros::v5::MotorUnits::degrees);
pros::MotorGroup MG_ARM({-10,11}, pros::v5::MotorGears::blue,
                        pros::v5::MotorUnits::degrees);

pros::Imu nimu(4);
pros::Imu rimu(-7);

double wheel_die = 2.72;

int avg_pos() {
  int avg_left = MG_Left.get_position();
  int avg_right = MG_Right.get_position();
  int avg_imu = nimu.get_heading() + rimu.get_heading();

  int avg = (avg_left + avg_right + avg_imu) / 2;

  return avg;
}

void drivef(double dist, std::int32_t velocity) {
  double r_dist = (dist / (numbers::pi * wheel_die) * 360);

  MG_Left.move_relative(r_dist, velocity);
  MG_Right.move_relative(r_dist, velocity);

  while (!(avg_pos() < r_dist + 5) && (avg_pos() > r_dist - 5)) {
    pros::delay(2);
  }
}

void spinf(double dist, std::int32_t velocity) {
  double r_dist = nimu.get_yaw() + rimu.get_yaw();

  MG_Left.move_relative(r_dist, velocity);
  MG_Right.move_relative(-r_dist, velocity);

  while(!(r_dist < dist + 5) && (r_dist > dist - 5)) {
    pros::delay(2);
  }
}

void auton_one() {
  drivef(-44, 600);

  pros::delay(1000);

  CEN_BOOL = !CEN_BOOL;
  ARM_BOOL = !ARM_BOOL;

  CEN.set_value(CEN_BOOL);

  pros::delay(10);

  ARM.set_value(ARM_BOOL);

  pros::delay(50);

  MG_Elr.move(-127 * 0.8);

  pros::delay(50);

}

void auton_two() {
  drivef(-55, 600);
  
  CEN_BOOL = !CEN_BOOL;
  CEN.set_value(CEN_BOOL);
  
  pros::delay(1);

  Elr.move(-127 * 0.8);

  pros::delay(5);

  spinf(-25, 600);

  drivef(-30, 600);
  spinf(-225, 600);
  drivef(30, 600);
  spinf(90, 600);
  drivef(300, 600);
  spinf(130, 600);
  drivef(55, 600);
}

void auton_skills() {
  
}

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
