#include "../include/main.h"
#include "../include/globle.hpp"
#include "pros/rtos.hpp"
#include "../include/autonTask.hpp"
#include "../include/auton.hpp"

void auton_one() {
  drivef(-10, 300);
  spinf(90, 300);
  
}

void autonomous() {
    auton_one();
}

