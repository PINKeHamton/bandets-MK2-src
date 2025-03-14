#include "../include/globle.hpp"
#include "pros/rtos.hpp"
#include <cstdint>
#include <numbers>

using namespace std;

#define WHEEL_DIE 2.72

#define TRAV_DIST(dist) (dist / (numbers::pi * WHEEL_DIE) * 360);

int avg_pos() {
  return (MG_Left.get_position() + MG_Right.get_position() +
          nimu.get_heading() + rimu.get_heading()) / 4;
}

void drivef(double dist, std::int32_t velocity) {
  double r_dist = TRAV_DIST(dist);

  MG_Left.move_relative(r_dist, velocity);
  MG_Right.move_relative(r_dist, velocity);

  while (true) {

  if(!(avg_pos() < r_dist + 10) && (avg_pos() > r_dist - 10)){
    
    pros::delay(2);
}
}
}

void spinf(double dist, std::int32_t velocity) {
  double r_dist = (nimu.get_heading() + rimu.get_heading()) /2;


  MG_Left.move_relative(r_dist, velocity);
  MG_Right.move_relative(-r_dist, velocity);


  if (!(r_dist < dist + 10) && (r_dist > dist - 10)) {
  }
}

void mvElr(double dist, std::int32_t velocity) {

  Elr.move_relative(dist, velocity);

  while (!(dist + 1) && (dist - 1)) {
    pros::delay(2);
  }
}

typedef enum pnuState {CEN_p, DONK_p, TRANS_p} PnuState;

void piston(int pnu) {
    switch (pnu) {
      case CEN_p:
        CEN_BOOL = !CEN_BOOL;
        CEN.set_value(CEN_BOOL);
    }
}
