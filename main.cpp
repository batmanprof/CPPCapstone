#include "screen.h"

int main() {

    Screen::InitNCurses();
    Screen screen(15);

    screen.loop();

    Screen::DeInitNCurses();
    return 0;
}
