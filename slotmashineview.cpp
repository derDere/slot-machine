#ifndef SLOTMASHINEVIEW_CPP
#define SLOTMASHINEVIEW_CPP

#include <ncursesw/ncurses.h>

#include "slotmashineview.hpp"
#include "slotmashine.hpp"

SlotMashineView::SlotMashineView(SlotMashine* slotMashine) {
  this->slotMashine = slotMashine;
  this->lightFrame = -1;
  this->leaverFrame = 0;
  this->coinFrane = -1;
  this->coinsFrame = -1;
  this->screenState = false;
}

SlotMashineView::~SlotMashineView() {
  this->slotMashine = NULL;
  this->lightFrame = 0;
  this->leaverFrame = 0;
  this->coinFrane = 0;
  this->coinsFrame = 0;
  this->screenState = false;
}

void SlotMashineView::clearScr() {

}

void SlotMashineView::printBase() {
  mvaddstr(
    0,
    0,
    "            ░░░             \n"
    "            ░░░             \n"
    "    ┌───────┴─┴───────┐     \n"
    "    │  J A C K P O T  │     \n"
    "    ├─────────────────┤     \n"
    "    │   ┌──┬──┬──┐    │     \n"
    "    │   │  │  │  │    │     \n"
    "    │   ├──┼──┼──┤    │     \n"
    "    │   │  │  │  │    │     \n"
    "    │   ├──┼──┼──┤    ├┐    \n"
    "    │   │  │  │  │    │├    \n"
    "    │   └──┴──┴──┘ ┌┐ │├    \n"
    "    │    ◌  ◌  ◌   ││ ├┘    \n"
    "    │              └┘ │     \n"
    "    ├─────────────────┤     \n"
    "    │ ┌─────────────┐ │     \n"
    "    │ │             │ │     \n"
    "    │ └─────────────┘ │     \n"
    "    ├─────────────────┤     \n"
    "    │      ┌───┐      │     \n"
    "  ┌─┴──────┘---└──────┴─┐   \n"
    "  │ Coins:              │   \n"
    "  └─────────────────────┘   \n"
  );
}

#endif
