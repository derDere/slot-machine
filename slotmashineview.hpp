#ifndef SLOTMASHINEVIEW_HPP
#define SLOTMASHINEVIEW_HPP

#include <ncursesw/ncurses.h>
#include "slotmashine.hpp"

class SlotMashineView;

class SlotMashineView {

  private:
    SlotMashine* slotMashine;
    int lightFrame;
    int leaverFrame;
    int coinFrane;
    int coinsFrame;
    bool screenState;

  public:
    SlotMashineView(SlotMashine*);
    ~SlotMashineView();

    void clearScr();
    void printBase();
};

#endif
