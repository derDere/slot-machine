#ifndef SLOTMASHINE_HPP
#define SLOTMASHINE_HPP

#include <ncursesw/ncurses.h>

#define SLOTS 3

class SlotMashine;

class SlotMashine {

  public:
    int wheels[SLOTS];
    bool leaver_down;
    bool won;
    bool lights[SLOTS];
    bool spinning;
    bool waiting;
    bool taking_coin;

    SlotMashine(int);
    ~SlotMashine();
};

#endif
