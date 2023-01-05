#ifndef SLOTMASHINE_HPP
#define SLOTMASHINE_HPP

#include <cstdlib>
#include <string>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <filesystem>
#include <ncursesw/ncurses.h>

#define SLOTS 3

#define VALUE_CHERRY 0
#define VALUE_LEMON 1
#define VALUE_BANNANA 2
#define VALUE_ORANGE 3
#define VALUE_APPLE 4
#define VALUE_MELON 5
#define VALUE_GRAPES 6
#define VALUE_LUCK 7
#define VALUE_BAR 8
#define VALUE_JEWL 9
#define VALUE_HEARTS 10
#define VALUE_DIAMONDS 11
#define VALUE_SPADES 12
#define VALUE_CLUBS 13
#define VALUE_SEVEN 14
#define VALUE_CROWN 15
#define VALUE_MAGNET 16
#define VALUE_BELL 17
#define VALUE_STAR 18
#define VALUE_MONEY 19

#define WHEEL_SIZE 20

using namespace std;

class SlotMashine;

class SlotMashine {

  public:
    void static getSlotValue(int, int&, int&);

    int wheels[SLOTS];
    bool leaver_down;
    bool won;
    bool lights[SLOTS];
    bool spinning;
    bool waiting;
    bool taking_coin;
    bool stopping;
    int rnd_delay[SLOTS];
    int money;
    int lastWin;
    string profile;

    SlotMashine(string, int);
    ~SlotMashine();

    void update(unsigned int);
    void pullLever();
    void insertCoin();
    void spin();
    void stop();

    void load_coins();
    void save_coins();

  private:
    void checkWin();
    string filePath();
};

#endif
