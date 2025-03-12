#include "../include/main.h"
#include "../include/globle.hpp"
#include "pros/rtos.hpp"
#include "../include/autonTask.hpp"

void auton_one() {
  drivef(-55, 500);

  CEN_BOOL = !CEN_BOOL;
  pros::delay(1000);
  CEN.set_value(CEN_BOOL);

  pros::delay(10);

  Elr.move(-127 * 0.8);

  pros::delay(50);
}

void auton_two() {
  drivef(-53, 300);

  CEN_BOOL = !CEN_BOOL;
  pros::delay(10);
  CEN.set_value(CEN_BOOL);

  Elr.move(-127 * 0.8);

  pros::delay(5);
}

void auton_skills() {
  
}

int auto_state = 1;

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
