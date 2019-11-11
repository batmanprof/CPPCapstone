#include "screen.h"
#include "game.h"

int main() {

    Screen::InitNCurses();

    Game game(15,5);
    Screen screen(game);

    screen.screenLogic();

    Screen::DeInitNCurses();
    return 0;
}
