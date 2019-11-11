#ifndef FIVE_IN_A_RAW_SCREEN
#define FIVE_IN_A_RAW_SCREEN
 
#include <ncurses.h>
#include "game.h"
class Screen {
public:
    Screen(Game &game);
    void loop();
    ~Screen();

    static void InitNCurses();
    static void DeInitNCurses();

private:
    int N;
    WINDOW *win;
    Game &game;

    int getNextStep();
    void printStatus();
    void waitForQuit();
};

#endif