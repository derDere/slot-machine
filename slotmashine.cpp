#ifndef SLOTMASHINE_CPP
#define SLOTMASHINE_CPP

#include <ncursesw/ncurses.h>

#include "slotmashine.hpp"

SlotMashine::SlotMashine(int start_coins) {
  for(int i = 0; i < SLOTS; i++) {
    this->wheels[i] = 0;
    this->lights[i] = false;
  }
  this->leaver_down = false;
  this->won = false;
  this->spinning = false;
  this->waiting = true;
  this->taking_coin = false;
}

SlotMashine::~SlotMashine() {
  for(int i = 0; i < SLOTS; i++) {
    this->wheels[i] = 0;
    this->lights[i] = false;
  }
  this->leaver_down = false;
  this->won = false;
  this->spinning = false;
  this->waiting = false;
  this->taking_coin = false;
}

#endif
