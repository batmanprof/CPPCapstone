#include "screen.h"
#include "game.h"

int main() {

    Screen::InitNCurses();

    Game game(9,5);
    Screen screen(game);

    screen.screenLogic();

    Screen::DeInitNCurses();
    return 0;
}
