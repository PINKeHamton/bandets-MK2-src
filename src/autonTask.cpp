#include "../include/globle.hpp"
#include "pros/rtos.hpp"
#include <cstdint>
#include <numbers>

using namespace std;

#define WHEEL_DIE 2.72

#define TRAV_DIST(dist) (dist / (numbers::pi * WHEEL_DIE) * 360);

#define errmar 3
#define errmarIMU 10
#define errmarELR 5

int avg_wheel() {
  return (MG_Left.get_position() + MG_Right.get_position()) /2;
}

int avg_imu() {
  return (nimu.get_heading() + rimu.get_heading()) / 2;
}

void drivef(double dist, std::int32_t velocity) {
  double r_dist = TRAV_DIST(dist);

  MG_Left.tare_position();
  MG_Right.tare_position();

  MG_Left.move_relative(r_dist, velocity);
  MG_Right.move_relative(r_dist, velocity);

  while(true){
    pros::delay(2);
    if (abs(r_dist - avg_wheel()) < errmar) {
        break;
    }
  }
}


void spinf(double dist, std::int32_t velocity) {
  double r_dist = (nimu.get_heading() + rimu.get_heading())/2;

  MG_Left.move(velocity);
  MG_Right.move(-velocity);

  while(true){
    pros::delay(2);
    if (abs(r_dist - avg_imu()) < errmarIMU) {
        break;
    }
  }
  MG_Left.brake();
  MG_Right.brake();
}

void mvElr(double dist, std::int32_t velocity) {
  Elr.tare_position();

  Elr.move(velocity);

  while(true){
    pros::delay(2);
    if (abs(dist - Elr.get_position()) < errmar) {
        break;
    }
  }
  Elr.brake();
}

typedef enum pnuState {CEN_p, DONK_p, TRANS_p} PnuState;

void piston(int pnu) {
    switch (pnu) {
      case CEN_p:
        CEN_BOOL = !CEN_BOOL;
        CEN.set_value(CEN_BOOL);
    }
}
