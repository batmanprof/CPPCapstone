#include "screen.h"
#include "game.h"

int main() {

    Screen::InitNCurses();

    Game game(10,4);
    Screen screen(game);

    screen.screenLogic();

    Screen::DeInitNCurses();
    return 0;
}
