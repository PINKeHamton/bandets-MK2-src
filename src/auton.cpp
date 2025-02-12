#include "../include/main.h"
#include <cstdint>
#include <numbers>
#include "../include/globle.hpp"

using namespace std;

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

  Elr.move(-127 * 0.8);

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
