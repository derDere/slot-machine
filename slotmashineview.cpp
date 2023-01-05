#ifndef SLOTMASHINEVIEW_CPP
#define SLOTMASHINEVIEW_CPP

#include <ncursesw/ncurses.h>

#include "slotmashineview.hpp"
#include "slotmashine.hpp"

using namespace std;

void SlotMashineView::Init() {
  init_pair(STYLE_NORMAL,       COLOR_WHITE,   COLOR_BLACK);
  init_pair(STYLE_LAMP_OFF,     COLOR_RED,     COLOR_BLACK);
  init_pair(STYLE_LAMP_ON,      COLOR_RED,     COLOR_WHITE);
  init_pair(STYLE_LAMP_SHINE,   COLOR_RED,     COLOR_BLACK);
  init_pair(STYLE_LIGHT_ON,     COLOR_RED,     COLOR_BLACK);
  init_pair(STYLE_LEVER_HEAD,   COLOR_RED,     COLOR_BLACK);
  init_pair(STYLE_SCREEN_FRAME, COLOR_BLACK,   COLOR_BLACK);
  init_pair(STYLE_SCREEN_TEXT,  COLOR_MAGENTA, COLOR_BLACK);
  init_pair(STYLE_MONEY,        COLOR_YELLOW,  COLOR_BLACK);
  init_pair(STYLE_TITLE,        COLOR_CYAN,    COLOR_BLACK);
  init_pair(STYLE_CARD_RED,     COLOR_RED,     COLOR_WHITE);
  init_pair(STYLE_CARD_BLACK,   COLOR_BLACK,   COLOR_WHITE);
  init_pair(STYLE_SEVEN,        COLOR_YELLOW,  COLOR_BLACK);
  init_pair(STYLE_DOLAR,        COLOR_GREEN,   COLOR_GREEN);
  init_pair(STYLE_ARROWS,       COLOR_BLUE,    COLOR_BLACK);
}

void addicon(int icon_val) {
  switch(icon_val) {
    case VALUE_CHERRY:
      addstr(ICON_CHERRY);
      break;
    case VALUE_LEMON:
      addstr(ICON_LEMON);
      break;
    case VALUE_BANNANA:
      addstr(ICON_BANNANA);
      break;
    case VALUE_ORANGE:
      addstr(ICON_ORANGE);
      break;
    case VALUE_APPLE:
      addstr(ICON_APPLE);
      break;
    case VALUE_MELON:
      addstr(ICON_MELON);
      break;
    case VALUE_GRAPES:
      addstr(ICON_GRAPES);
      break;
    case VALUE_LUCK:
      addstr(ICON_LUCK);
      break;
    case VALUE_BAR:
      addstr(ICON_BAR);
      break;
    case VALUE_JEWL:
      addstr(ICON_JEWL);
      break;
    case VALUE_HEARTS:
      attron(COLOR_PAIR(STYLE_CARD_RED));
      addstr(ICON_HEARTS);
      attroff(COLOR_PAIR(STYLE_CARD_RED));
      break;
    case VALUE_DIAMONDS:
      attron(COLOR_PAIR(STYLE_CARD_RED));
      addstr(ICON_DIAMONDS);
      attroff(COLOR_PAIR(STYLE_CARD_RED));
      break;
    case VALUE_SPADES:
      attron(COLOR_PAIR(STYLE_CARD_BLACK));
      addstr(ICON_SPADES);
      attroff(COLOR_PAIR(STYLE_CARD_BLACK));
      break;
    case VALUE_CLUBS:
      attron(COLOR_PAIR(STYLE_CARD_BLACK));
      addstr(ICON_CLUBS);
      attroff(COLOR_PAIR(STYLE_CARD_BLACK));
      break;
    case VALUE_SEVEN:
      attron(COLOR_PAIR(STYLE_SEVEN));
      addstr(ICON_SEVEN);
      attroff(COLOR_PAIR(STYLE_SEVEN));
      break;
    case VALUE_CROWN:
      addstr(ICON_CROWN);
      break;
    case VALUE_MAGNET:
      addstr(ICON_MAGNET);
      break;
    case VALUE_BELL:
      addstr(ICON_BELL);
      break;
    case VALUE_STAR:
      addstr(ICON_STAR);
      break;
    case VALUE_MONEY:
      attron(A_DIM);
      attron(COLOR_PAIR(STYLE_DOLAR));
      addstr(ICON_MONEY);
      attroff(COLOR_PAIR(STYLE_DOLAR));
      attroff(A_DIM);
      break;
  }
}

SlotMashineView::SlotMashineView(SlotMashine* slotMashine) {
  this->slotMashine = slotMashine;
  this->lightFrame = 0;
  this->leverFrame = 0;
  this->coinFrame = -1;
  this->coinsFrame = 0;
  this->blink = false;
}

SlotMashineView::~SlotMashineView() {
  this->slotMashine = NULL;
  this->lightFrame = 0;
  this->leverFrame = 0;
  this->coinFrame = 0;
  this->coinsFrame = 0;
  this->blink = false;
}

void SlotMashineView::update(unsigned int tick) {

  // Lever flip
  if (this->leverFrame < 9 && this->slotMashine->leaver_down) {
    this->leverFrame++;
    if (this->leverFrame >= 9 && this->slotMashine->spinning) {
      this->slotMashine->stop();
    }
  } else if (this->leverFrame > 0 && !(this->slotMashine->leaver_down)) {
    this->leverFrame--;
  } else {
    this->slotMashine->leaver_down = false;
  }

  // light anim
  this->lightFrame++;
  this->lightFrame %= 16;

  // light anim
  if ((tick % 4) == 0) {
    this->coinsFrame++;
    this->coinsFrame %= 11;
  }

  // coin anim
  if (this->slotMashine->taking_coin) {
    if ((tick % 4) == 0) {
      this->coinFrame++;
    }
  } else {
    this->coinFrame = -1;
  }

  // blinking
  if ((tick % 8) == 0) {
    this->blink = !(this->blink);
  }
}

void SlotMashineView::print() {
  this->printBase();
  this->printLamps();
  this->printLight();
  this->printLever();
  this->printCoin();
  this->printScreen();
  this->printMoney();
  this->printCoins();
  this->printWheels();
  this->printPoints();
}

void SlotMashineView::printBase() {
  mvaddstr(
    0,
    0,
    "            ");
  attron(A_DIM);
  attron(COLOR_PAIR(STYLE_LAMP_OFF));
  addstr(       "░░░             \n"
    "            ░░░             \n");
  attroff(COLOR_PAIR(STYLE_LAMP_OFF));
  attroff(A_DIM);
  addstr(
    "    ┌───────┴─┴───────┐     \n"
    "    │  ");
  attron(COLOR_PAIR(STYLE_TITLE));
  addstr("J A C K P O T");
  attroff(COLOR_PAIR(STYLE_TITLE));
  addstr(
                        "  │     \n"
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
    "  │                     │   \n"
    "  │                     │   \n"
    "  └─────────────────────┘   \n"
  );
  attron(A_BOLD);
  attron(COLOR_PAIR(STYLE_SCREEN_FRAME));
  mvaddstr(15, 6, "┌─────────────┐");
  mvaddstr(16, 6, "│             │");
  mvaddstr(17, 6, "└─────────────┘");
  attroff(COLOR_PAIR(STYLE_SCREEN_FRAME));

  attron(COLOR_PAIR(STYLE_ARROWS));
  mvaddstr(8,  6, "►");
  mvaddstr(8, 19, "◄");
  attroff(COLOR_PAIR(STYLE_SCREEN_FRAME));
  attroff(A_BOLD);
}

void SlotMashineView::printLever() {
  switch(this->leverFrame) {
    case 0:
      attron(COLOR_PAIR(STYLE_LEVER_HEAD));
      mvaddstr( 4, 23, "╭───╮");
      mvaddstr( 5, 23, "│   │");
      mvaddstr( 6, 23, "╰┬─┬╯");
      attroff(COLOR_PAIR(STYLE_LEVER_HEAD));
      mvaddstr( 7, 24,  "│ │");
      mvaddstr( 8, 24,  "│ │");
      mvaddstr( 9, 24,  "│ │");
      mvaddstr(10, 24,  "┘ │");
      mvaddstr(11, 24,  "──┘");
      break;
    case 1:
      attron(COLOR_PAIR(STYLE_LEVER_HEAD));
      mvaddstr( 5, 23, "╭───╮");
      mvaddstr( 6, 23, "│  ╮│");
      mvaddstr( 7, 23, "╰┬─┬╯");
      attroff(COLOR_PAIR(STYLE_LEVER_HEAD));
      mvaddstr( 8, 24,  "│ │");
      mvaddstr( 9, 24,  "│ │");
      mvaddstr(10, 24,  "┘ │");
      mvaddstr(11, 24,  "──┘");
      break;
    case 2:
      attron(COLOR_PAIR(STYLE_LEVER_HEAD));
      mvaddstr( 6, 23, "╭───╮");
      mvaddstr( 7, 23, "│   │");
      mvaddstr( 8, 23, "╰┬─┬╯");
      attroff(COLOR_PAIR(STYLE_LEVER_HEAD));
      mvaddstr( 9, 24,  "│ │");
      mvaddstr(10, 24,  "┘ │");
      mvaddstr(11, 24,  "──┘");
      break;
    case 3:
      attron(COLOR_PAIR(STYLE_LEVER_HEAD));
      mvaddstr( 7, 23, "╭───╮");
      mvaddstr( 8, 23, "│   │");
      mvaddstr( 9, 23, "╰┬─┬╯");
      attroff(COLOR_PAIR(STYLE_LEVER_HEAD));
      mvaddstr(10, 24,  "┘ │");
      mvaddstr(11, 24,  "──┘");
      break;
    case 4:
      attron(COLOR_PAIR(STYLE_LEVER_HEAD));
      mvaddstr( 8, 23, "╭───╮");
      mvaddstr( 9, 23, "│   │");
      mvaddstr(10, 23, "╰┬─┬╯");
      attroff(COLOR_PAIR(STYLE_LEVER_HEAD));
      mvaddstr(11, 24,  "──┘");
      break;
    case 5:
      attron(COLOR_PAIR(STYLE_LEVER_HEAD));
      mvaddstr( 9, 23, "╭───╮");
      mvaddstr(10, 23, "│   │");
      mvaddstr(11, 23, "╰───╯");
      attroff(COLOR_PAIR(STYLE_LEVER_HEAD));
      break;
    case 6:
      attron(COLOR_PAIR(STYLE_LEVER_HEAD));
      mvaddstr(10, 23, "╭───╮");
      mvaddstr(11, 23, "│   │");
      mvaddstr(12, 23, "╰───╯");
      attroff(COLOR_PAIR(STYLE_LEVER_HEAD));
      break;
    case 7:
      mvaddstr(10, 24,  "──┐");
      attron(COLOR_PAIR(STYLE_LEVER_HEAD));
      mvaddstr(11, 23, "╭┴─┴╮");
      mvaddstr(12, 23, "│   │");
      mvaddstr(13, 23, "╰───╯");
      attroff(COLOR_PAIR(STYLE_LEVER_HEAD));
      break;
    case 8:
      mvaddstr(10, 24,  "──┐");
      mvaddstr(11, 24,  "┐ │");
      attron(COLOR_PAIR(STYLE_LEVER_HEAD));
      mvaddstr(12, 23, "╭┴─┴╮");
      mvaddstr(13, 23, "│   │");
      mvaddstr(14, 23, "╰───╯");
      attroff(COLOR_PAIR(STYLE_LEVER_HEAD));
      break;
    default:
      mvaddstr(10, 24,  "──┐");
      mvaddstr(11, 24,  "┐ │");
      mvaddstr(12, 24,  "│ │");
      attron(COLOR_PAIR(STYLE_LEVER_HEAD));
      mvaddstr(13, 23, "╭┴─┴╮");
      mvaddstr(14, 23, "│   │");
      mvaddstr(15, 23, "╰───╯");
      attroff(COLOR_PAIR(STYLE_LEVER_HEAD));
      break;
  }
}

void SlotMashineView::printLamps() {
  for(int i = 0; i < SLOTS; i++) {
    if (this->slotMashine->lights[i]) {
      attron(COLOR_PAIR(STYLE_LIGHT_ON));
      mvaddstr(12, 9 + (i * 3), "●");
      attroff(COLOR_PAIR(STYLE_LIGHT_ON));
    } else {
      mvaddstr(12, 9 + (i * 3), "◌");
    }
  }
}

void SlotMashineView::printLight() {
  if(!this->slotMashine->won) return;
  attron(A_BOLD);
  if ( this->blink ) {
    attron(COLOR_PAIR(STYLE_LAMP_SHINE));
    mvaddstr(0,  9, "_\\     /_");
    mvaddstr(1, 10,   "/     \\");
    mvaddstr(3,  7, "J A C K P O T");
    attroff(COLOR_PAIR(STYLE_LAMP_SHINE));
  }
  attron(COLOR_PAIR(STYLE_LAMP_ON));
  switch(this->lightFrame) {
    case 0:
    case 1:
      mvaddstr(0, 12, "███");
      mvaddstr(1, 12, "███");
      break;
    case 2:
    case 3:
      mvaddstr(0, 12, "██▓");
      mvaddstr(1, 12, "███");
      break;
    case 4:
    case 5:
      mvaddstr(0, 12, "█▓▒");
      mvaddstr(1, 12, "██▓");
      break;
    case 6:
    case 7:
      mvaddstr(0, 12, "▓▒░");
      mvaddstr(1, 12, "█▓▒");
      break;
    case 8:
    case 9:
      mvaddstr(0, 12, "▒░ ");
      mvaddstr(1, 12, "▓▒░");
      break;
    case 10:
    case 11:
      mvaddstr(0, 12, "░ █");
      mvaddstr(1, 12, "▒░ ");
      break;
    case 12:
    case 13:
      mvaddstr(0, 12, " ██");
      mvaddstr(1, 12, "░ █");
      break;
    case 14:
    case 15:
      mvaddstr(0, 12, "███");
      mvaddstr(1, 12, " ██");
      break;
  }
  attroff(COLOR_PAIR(STYLE_LAMP_ON));
  attroff(A_BOLD);
}

void SlotMashineView::printCoin() {
  if (!(this->slotMashine->taking_coin)) return;
  attron(A_BOLD);
  attron(COLOR_PAIR(STYLE_MONEY));
  switch(this->coinFrame) {
    case 0:
      mvaddstr(12, 21, "($)");
      break;
    case 1:
      mvaddstr(12, 20, "($)");
      break;
    case 2:
      mvaddstr(12, 20, "$)");
      break;
    case 3:
      mvaddstr(12, 20, ")");
      break;
    case 4:
      this->slotMashine->spin();
      break;
  }
  attroff(COLOR_PAIR(STYLE_MONEY));
  attroff(A_BOLD);
}

void SlotMashineView::printCoins() {
  if (!(this->slotMashine->won)) return;
  attron(A_BOLD);
  attron(COLOR_PAIR(STYLE_MONEY));
  switch(this->coinsFrame) {
    case 0:
      mvaddstr(20, 12, "o  ");
      mvaddstr(21, 12, "o o");
      mvaddstr(22, 12, "oo ");
      break;
    case 1:
      mvaddstr(20, 12, " o ");
      mvaddstr(21, 12, "o  ");
      mvaddstr(22, 12, "o o");
      break;
    case 2:
      mvaddstr(20, 12, "o o");
      mvaddstr(21, 12, " o ");
      mvaddstr(22, 12, "o  ");
      break;
    case 3:
      mvaddstr(20, 12, "oo ");
      mvaddstr(21, 12, "o o");
      mvaddstr(22, 12, " o ");
      break;
    case 4:
      mvaddstr(20, 12, " oo");
      mvaddstr(21, 12, "oo ");
      mvaddstr(22, 12, "o o");
      break;
    case 5:
      mvaddstr(20, 12, "o o");
      mvaddstr(21, 12, " oo");
      mvaddstr(22, 12, "oo ");
      break;
    case 6:
      mvaddstr(20, 12, " o ");
      mvaddstr(21, 12, "o o");
      mvaddstr(22, 12, " oo");
      break;
    case 7:
      mvaddstr(20, 12, "o  ");
      mvaddstr(21, 12, " o ");
      mvaddstr(22, 12, "o o");
      break;
    case 8:
      mvaddstr(20, 12, "  o");
      mvaddstr(21, 12, "o  ");
      mvaddstr(22, 12, " o ");
      break;
    case 9:
      mvaddstr(20, 12, "oo ");
      mvaddstr(21, 12, "  o");
      mvaddstr(22, 12, "o  ");
      break;
    case 10:
      mvaddstr(20, 12, "o o");
      mvaddstr(21, 12, "oo ");
      mvaddstr(22, 12, "  o");
      break;
  }
  attroff(COLOR_PAIR(STYLE_MONEY));
  attroff(A_BOLD);
}

void SlotMashineView::printScreen() {
  attron(COLOR_PAIR(STYLE_SCREEN_TEXT));
  if (this->slotMashine->won && this->blink) {
    attron(A_BOLD);
    mvaddstr(16,  8, "  WINNER!  ");
    attroff(A_BOLD);
  }
  else if ((this->slotMashine->waiting || this->slotMashine->taking_coin) && this->blink) {
    mvaddstr(16,  8, "Insert Coin");
  }
  else if (this->slotMashine->spinning && this->blink) {
    mvaddstr(16,  8, "Pull  Lever");
  }
  attroff(COLOR_PAIR(STYLE_SCREEN_TEXT));
}

void SlotMashineView::printWheels() {
  int wheelsTop[3];
  int wheelsBot[3];

  for(int i = 0; i < SLOTS; i++) {
    wheelsTop[i] = this->slotMashine->wheels[i] - 1;
    wheelsBot[i] = this->slotMashine->wheels[i] + 1;
    wheelsTop[i] = (wheelsTop[i] + WHEEL_SIZE) % WHEEL_SIZE;
    wheelsBot[i] %= WHEEL_SIZE;
  }

  int* wheelsL[3] = {
    wheelsTop,
    this->slotMashine->wheels,
    wheelsBot
  };

  for (int y = 0; y < 3; y++) {
    for(int x = 0; x < SLOTS; x++) {
      move(6 + (y * 2), 9 + (x * 3));
      addicon(wheelsL[y][x]);
    }
  }
}

void SlotMashineView::printMoney() {
  attron(COLOR_PAIR(STYLE_MONEY));
  attron(A_BOLD);
  mvprintw(21, 4, "Coins:%13i", this->slotMashine->money);
  attroff(A_BOLD);
  mvprintw(22, 4, "Last: %13i", this->slotMashine->lastWin);
  attroff(COLOR_PAIR(STYLE_MONEY));
}

void SlotMashineView::printPoints() {
  attron(A_UNDERLINE);
  mvaddstr(2, 35, "ICO    2x    3x");
  attroff(A_UNDERLINE);
  for(int slot = 0; slot < WHEEL_SIZE; slot++) {
    int d, t;
    SlotMashine::getSlotValue(slot, d, t);
    move(3 + (slot), 35);
    addicon(slot);
    printw(":   %3i   %3i", d, t);
  }
}

#endif
