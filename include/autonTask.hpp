#include "../include/globle.hpp"
#include <cstdint>

#ifndef _AUTONTASK_HPP_
#define _AUTONTASK_HPP_ 

int avg_pos();

void drivef(double dist, std::int32_t velocity);
void spinf(double dist, std::int32_t velocity);

void mvElr(double dist, std::int32_t velocity);

typedef enum pnuState {CEN_p, DONK_p, TRANS_p} PnuState;

void piston(int pnu);

#endif
