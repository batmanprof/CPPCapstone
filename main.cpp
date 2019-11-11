#include "screen.h"
#include "game.h"

int main() {

    Screen::InitNCurses();

    Game game(15,5);
    Screen screen(game);

    screen.loop();

    Screen::DeInitNCurses();
    return 0;
}
