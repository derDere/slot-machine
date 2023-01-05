#ifndef SLOTMASHINEVIEW_HPP
#define SLOTMASHINEVIEW_HPP

#include <ncursesw/ncurses.h>
#include "slotmashine.hpp"

#define STYLE_NORMAL 1
#define STYLE_LAMP_OFF 2
#define STYLE_LAMP_ON 3
#define STYLE_LAMP_SHINE 4
#define STYLE_LIGHT_ON 5
#define STYLE_LIGHT_OFF 6
#define STYLE_LEVER_HEAD 7
#define STYLE_SCREEN_FRAME 8
#define STYLE_SCREEN_TEXT 9
#define STYLE_MONEY 10
#define STYLE_TITLE 11
#define STYLE_CARD_RED 12
#define STYLE_CARD_BLACK 13
#define STYLE_SEVEN 14
#define STYLE_DOLAR 15
#define STYLE_ARROWS 16

#define ICON_CHERRY "🍒"
#define ICON_LEMON "🍋"
#define ICON_BANNANA "🍌"
#define ICON_ORANGE "🍊"
#define ICON_APPLE "🍎"
#define ICON_MELON "🍉"
#define ICON_GRAPES "🍇"
#define ICON_LUCK "🍀"
#define ICON_BAR "⛔"
#define ICON_JEWL "💎"
#define ICON_HEARTS "♥A"
#define ICON_DIAMONDS "♦A"
#define ICON_SPADES "♠A"
#define ICON_CLUBS "♣A"
#define ICON_SEVEN "7 "
#define ICON_CROWN "👑"
#define ICON_MAGNET "🧲"
#define ICON_BELL "🔔"
#define ICON_STAR "⭐"
#define ICON_MONEY "▌$"

using namespace std;

class SlotMashineView;

class SlotMashineView {

  private:
    SlotMashine* slotMashine;
    int lightFrame;
    int leverFrame;
    int coinFrame;
    int coinsFrame;
    bool blink;

  public:
    static void Init();

    SlotMashineView(SlotMashine*);
    ~SlotMashineView();

    void update(unsigned int);
    void print();

  private:
    void printBase();
    void printLever();
    void printLamps();
    void printLight();
    void printCoin();
    void printCoins();
    void printScreen();
    void printWheels();
    void printMoney();
    void printPoints();
};

#endif
