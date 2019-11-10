#ifndef FIVE_IN_A_RAW_SCREEN
#define FIVE_IN_A_RAW_SCREEN
 
#include <ncurses.h>

class Screen {
public:
    Screen(int N=15);
    void loop();
    ~Screen();

    static void InitNCurses();
    static void DeInitNCurses();

private:
    int N;
    WINDOW *win;
};

#endif