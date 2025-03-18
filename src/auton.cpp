#include "../include/main.h"
#include "../include/globle.hpp"
#include "pros/rtos.hpp"
#include "../include/autonTask.hpp"
#include "../include/auton.hpp"

void auton_one() {
  drivef(55, 300);
  piston(CEN_p);
  mvElr(20, -300);
}

void auton_two() {
  drivef(-10, 600);
  spinf(-90, 300);
  mvElr(10, 600);
  spinf(-140, 300);
}

void auton_three() {}

void autonomous() {
  auton_one();
}

