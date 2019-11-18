#ifndef FIVE_IN_A_RAW_SCREEN
#define FIVE_IN_A_RAW_SCREEN
 
#include <ncurses.h>
#include <memory>

#include "game.h"
#include "ai.h"

class Screen {
public:
    Screen(Game &igame);
    void screenLogic();
    ~Screen();

    static void InitNCurses();
    static void DeInitNCurses();

private:
    int N;
    Game &game;
    std::unique_ptr<AI> aiX=nullptr;
    std::unique_ptr<AI> aiO=nullptr;

    WINDOW *win;

    int getNextStep();
    bool processPlayerStep(); //returns true, if player chose to exit
    void processAIStep(int x, int y); 
    void printStatus();
    void waitForQuit();
    void showWinner();
};

#endif