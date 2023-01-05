#ifndef SLOTMASHINE_CPP
#define SLOTMASHINE_CPP

#include "slotmashine.hpp"

using namespace std;

void SlotMashine::getSlotValue(int slot, int& duo, int& tripple) {
  switch(slot) {
    case VALUE_CHERRY:   duo =  1; tripple =   5; return;
    case VALUE_LEMON:    duo =  1; tripple =   5; return;
    case VALUE_BANNANA:  duo =  1; tripple =   5; return;
    case VALUE_ORANGE:   duo =  1; tripple =   5; return;
    case VALUE_APPLE:    duo =  1; tripple =   5; return;

    case VALUE_MELON:    duo =  2; tripple =  10; return;
    case VALUE_GRAPES:   duo =  2; tripple =  10; return;

    case VALUE_BAR:      duo =  0; tripple =   0; return;

    case VALUE_LUCK:     duo =  4; tripple =  25; return;
    case VALUE_JEWL:     duo =  4; tripple =  25; return;

    case VALUE_HEARTS:   duo =  8; tripple =  50; return;
    case VALUE_DIAMONDS: duo =  8; tripple =  50; return;
    case VALUE_SPADES:   duo =  8; tripple =  50; return;
    case VALUE_CLUBS:    duo =  8; tripple =  50; return;

    case VALUE_CROWN:    duo = 10; tripple =  75; return;
    case VALUE_MAGNET:   duo = 10; tripple =  75; return;

    case VALUE_BELL:     duo = 15; tripple = 100; return;
    case VALUE_STAR:     duo = 15; tripple = 100; return;

    case VALUE_MONEY:    duo = 25; tripple = 150; return;

    case VALUE_SEVEN:    duo = 50; tripple = 500; return;
  }
}

SlotMashine::SlotMashine(string profile, int start_coins) {
  for(int i = 0; i < SLOTS; i++) {
    this->wheels[i] = rand() % WHEEL_SIZE;
    this->lights[i] = false;
    this->rnd_delay[i] = 0;
  }
  this->leaver_down = false;
  this->won = false;
  this->spinning = false;
  this->waiting = true;
  this->taking_coin = false;
  this->money = start_coins;
  this->load_coins();
  this->stopping = false;
  this->lastWin = 0;
  this->profile = profile;
}

SlotMashine::~SlotMashine() {
  for(int i = 0; i < SLOTS; i++) {
    this->wheels[i] = 0;
    this->lights[i] = false;
    this->rnd_delay[i] = 0;
  }
  this->leaver_down = false;
  this->won = false;
  this->spinning = false;
  this->waiting = false;
  this->taking_coin = false;
  this->money = 0;
  this->stopping = false;
  this->lastWin = 0;
}

void SlotMashine::update(unsigned int tick) {
  if (this->spinning && (tick % 2) == 0) {
    for(int i = 0; i < SLOTS; i++) {
      this->wheels[i]--;
      this->wheels[i] += WHEEL_SIZE;
      this->wheels[i] %= WHEEL_SIZE;
    }
  }
  if (this->stopping && (tick % 4) == 0) {
    bool still_stopping = false;
    for(int i = 0; i < SLOTS; i++) {
      if (this->rnd_delay[i] > 0) {
        this->wheels[i]--;
        this->wheels[i] += WHEEL_SIZE;
        this->wheels[i] %= WHEEL_SIZE;
        this->rnd_delay[i]--;
        still_stopping = true;
      }
    }
    if (!still_stopping) {
      this->waiting = true;
      this->stopping = false;
      this->checkWin();
    }
  }
}

void SlotMashine::stop() {
  if (!(this->stopping)) {
    this->stopping = true;
    this->spinning = false;
    for(int i = 0; i < SLOTS; i++) {
      this->rnd_delay[i] = (3 + (rand() % (WHEEL_SIZE * 2)));
    }
  }
}

void SlotMashine::pullLever() {
  if (this->spinning && !(this->taking_coin) && !(this->stopping)) {
    this->leaver_down = true;
  }
}

void SlotMashine::insertCoin() {
  if (this->waiting && !(this->taking_coin)) {
    this->money--;
    this->waiting = false;
    this->taking_coin = true;
    this->save_coins();
  }
}

void SlotMashine::spin() {
  this->taking_coin = false;
  this->spinning = true;
  for(int i = 0; i < SLOTS; i++) {
    this->lights[i] = false;
  }
  this->won = false;
}

void SlotMashine::checkWin() {
  int coins = 1;

  int s1 = this->wheels[0];
  int s2 = this->wheels[1];
  int s3 = this->wheels[2];

  int m = 0, _;

  if (s1 == s2 && s2 == s3) {
    SlotMashine::getSlotValue(s1, _, m);
    for(int i = 0; i < SLOTS; i++) {
      this->lights[i] = true;
    }
    this->won = true;
  }
  else if (s1 == s2) {
    this->lights[0] = true;
    this->lights[1] = true;
    SlotMashine::getSlotValue(s1, m, _);
  }
  else if (s2 == s3) {
    this->lights[1] = true;
    this->lights[2] = true;
    SlotMashine::getSlotValue(s2, m, _);
  }
  else if (s1 == s3) {
    this->lights[0] = true;
    this->lights[2] = true;
    SlotMashine::getSlotValue(s1, m, _);
  }

  coins *= m;

  if (s1 == VALUE_BAR || s2 == VALUE_BAR || s3 == VALUE_BAR) {
    coins = 0;
  }

  this->lastWin = coins;

  this->money += coins;

  this->save_coins();
}

bool dirExists(const char *path) {
    struct stat info;
    if(stat( path, &info ) != 0)
        return false;
    else if(info.st_mode & S_IFDIR)
        return true;
    else
        return false;
}

string SlotMashine::filePath() {
  string homeDir(getenv("HOME"));
  string path("/.config/slot-machine/");
  path = homeDir + path;
  if (!dirExists(path.c_str())) {
    filesystem::create_directory(path);
  }
  path += this->profile;
  return path;
}

#include <stdlib.h>

void SlotMashine::load_coins() {
  ifstream coin_file(this->filePath());
  //if (coin_file.good()) {
  int coins = 55;
  coin_file >> coins;
  endwin();
  cout << "CCC: " << coins << endl;
  cout << "CCC: " << coins << endl;
  cout << "CCC: " << coins << endl;
  cout << "CCC: " << coins << endl;
  cout << "CCC: " << coins << endl;
  cout << "CCC: " << coins << endl;
  exit(0);
  this->money = coins;
  coin_file.close();
  //}
}

void SlotMashine::save_coins() {
  ofstream coin_file(this->filePath(), ios::out | fstream::trunc);
  coin_file << this->money << " " << endl;
  coin_file.close();
}

#endif
