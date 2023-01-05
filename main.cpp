#ifndef MAIN_CPP
#define MAIN_CPP

#include <string>
#include <iostream>
//#include <limits>
//#include <iomanip>
//#include <cstdlib>
#include <ncursesw/ncurses.h>

#include "slotmashineview.hpp"
#include "slotmashine.hpp"

#ifdef _WIN32
#include <Windows.h>
#define SLEEP(ms) Sleep(ms)
#else
#include <unistd.h>
#define SLEEP(ms) usleep(ms * 1000)
#endif

#define FPS 30
#define START_COINS 15

using namespace std;

void quit();
void printHelp();

/**
 * Project: slot-machine
 * Creator: deremer
 * Creation Date: Tue Sep 13 11:31:51 CEST 2022
 */
int main(int argc, const char* argv[]) {

  const char* profile = "default";
  bool reset_profile = false;

  // Check Command Line Arguments ----------
  for(int i = 0; i < argc; i++) {
    string arg(argv[i]);
    if (
      (arg == "-?") ||
      (arg == "/?") ||
      (arg == "help") ||
      (arg == "--help")
    ) {
      cout << "Usage: slot-machine [options]" << endl
           << endl
           << "Options:" << endl
           << "  -p <profile>      Changes to another profile." << endl
           << "  -r                Resets the current profile." << endl
           << endl
           << "About:" << endl
           << "  Just play a bit slot mashine." << endl
           << endl
           << "Key bindings:" << endl
           << "  SPACE       leaver down" << endl
           << "  c           insert coin" << endl
           << "  h           show/hide help" << endl
           << "  q           quit" << endl
           << endl;
      return 0;
    }
    else if (arg == "-p" && argc > (i + 1)) {
      profile = argv[++i];
    }
    else if (arg == "-r") {
      reset_profile = true;
    }
    else {
        // unknown argument
    }
  }

  // Init Curses ----------
  setlocale(LC_ALL, "");
  WINDOW* win = initscr();
  atexit(quit);
  curs_set(0);
  start_color();
  clear();
  noecho();
  cbreak();
  keypad(stdscr, true);
  //mousemask(BUTTON1_CLICKED, NULL); //ALL_MOUSE_EVENTS, NULL);
  SlotMashineView::Init();

  // Check Size ----------
  //int cols, rows;
  //getmaxyx(stdscr, rows, cols);
  // TODO: Check Size ############################################

  // Draw Start Screen ----------
  attron(A_DIM);
  mvprintw(0, 0, "Profile: %s", profile);
  attroff(A_DIM);
  printHelp();
  attron(A_BOLD);
  mvaddstr(11, 7, "Press any key to start...");
  attroff(A_BOLD);
  getch();
  nodelay(win, true);

  // Clear screen ----------
  clear();

  // Create Objects
  unsigned int tick = 0;
  bool showHelp = false;
  SlotMashine* slotMashine = new SlotMashine(string(profile), START_COINS);
  SlotMashineView* slotMashineView = new SlotMashineView(slotMashine);

  // Reset provile if option was given
  if (reset_profile) {
    slotMashine->money = START_COINS;
  }

  // Start main loop
  bool run = true;
  int key = '?';
  while (run) {
    SLEEP(1000 / FPS);
    if (showHelp) {
      printHelp();
    } else {
      slotMashineView->print();
    }
    key = getch();
    switch(key) {
      case ' ':
        slotMashine->pullLever();
        break;
      case 'c':
        slotMashine->insertCoin();
        break;
      case 'h':
        clear();
        showHelp = !showHelp;
        break;
      case 'q':
        run = false;
        break;
    }
    key = '?';
    slotMashine->update(tick);
    slotMashineView->update(tick++);
  }
  return 0;
}

void printHelp() {
  attron(A_BOLD | A_UNDERLINE);
  mvaddstr( 3, 5, "Slot Machine");
  attroff(A_UNDERLINE);
  mvaddstr( 5, 7, "Key bindings:");
  attroff(A_BOLD);
  mvaddstr( 6, 9, "SPACE  leaver down");
  mvaddstr( 7, 9, "q      quit");
  mvaddstr( 8, 9, "c      insert coin");
  mvaddstr( 9, 9, "h      show/hide help");
}

void quit() {
  endwin();
}

#endif
