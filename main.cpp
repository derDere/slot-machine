#ifndef MAIN_CPP
#define MAIN_CPP

#include <iostream>
//#include <limits>
//#include <iomanip>
//#include <cstdlib>
#include <ncursesw/ncurses.h>

#include "slotmashineview.hpp"
#include "slotmashine.hpp"

#ifdef _WIN32
//#include <Windows.h>
#else
//#include <unistd.h>
#endif

using namespace std;

void quit();

/**
 * Project: slot-machine
 * Creator: deremer
 * Creation Date: Tue Sep 13 11:31:51 CEST 2022
 */
int main(int argc, char* argv[]) {

  // Check Command Line Arguments ----------
  for(int i = 0; i < argc; i++) {
    string arg(argv[i]);
    if (
      (arg == "-?") ||
      (arg == "/?") ||
      (arg == "help") ||
      (arg == "--help")
    ) {
      cout << "Usage: slot-machine" << endl
           << endl
           << "About:" << endl
           << "  Just play a bit slot mashine." << endl
           << endl
           << "Key bindings:" << endl
           << "  SPACE       leaver down" << endl
           << "  c           insert coin" << endl
           << "  h           show help" << endl
           << "  q           quit" << endl
           << endl;
      return 0;
    } else {
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
  mousemask(BUTTON1_CLICKED, NULL); //ALL_MOUSE_EVENTS, NULL);

  // Check Size ----------
  int cols, rows;
  getmaxyx(stdscr, rows, cols);
  // TODO: Check Size ############################################

  // Draw Start Screen ----------
  attron(A_BOLD | A_UNDERLINE);
  mvaddstr( 3, 5, "Slot Machine");
  attroff(A_UNDERLINE);
  mvaddstr( 5, 7, "Key bindings:");
  attroff(A_BOLD);
  mvaddstr( 6, 9, "SPACE  leaver down");
  mvaddstr( 7, 9, "q      quit");
  mvaddstr( 8, 9, "c      insert coin");
  mvaddstr( 9, 9, "h      show help");
  attron(A_BOLD);
  mvaddstr(11, 7, "Press any key to start...");
  attroff(A_BOLD);
  getch();
  nodelay(win, true);

  // Clear screen ----------
  for (int i = 0; i < 12; i++) {
    mvaddstr(i, 5, "                             ");
  }

  // Create Objects
  SlotMashine* slotMashine = new SlotMashine(15);
  SlotMashineView* slotMashineView = new SlotMashineView(slotMashine);

  // Start main loop
  bool run = true;
  int key = ' ';
  while (run) {
    slotMashineView->printBase();
    key = getch();
    switch(key) {
      case 'q':
        run = false;
        break;
    }
    key = ' ';
  }

  return 0;
}

void quit() {
  endwin();
}

#endif
