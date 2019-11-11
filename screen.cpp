#include "screen.h"

#include <iostream>
#include <string>
#include <memory>
#include <ncurses.h>


Screen::Screen(Game &game):game(game),N(game.size()){
    //Letters - horizontal
    printw("   ");
    for(int i=0;i<N;i++) {
    addch(65+i);
    }
    //Numbers - vertical
    for(int i=1;i<=N;i++){
        if (i<10) {
            mvprintw(i+1,1,std::to_string(i).c_str());
        } else {
            mvprintw(i+1,0,std::to_string(i).c_str());
        }
    }
    mvprintw(N+4,0,"Use arrow-keys and");
    mvprintw(N+5,0,"space-key to play.");
    mvprintw(N+6,0,"Press 'q' to quit.");
    refresh();

    //Create the play area as window
    win = newwin(N+2, N+2, 1, 2);
    box(win,0,0);
    //mvwaddch(win,3,3,'a');
    wmove(win, N/2+1, N/2+1);
    wrefresh(win);		
}

int Screen::getNextStep(){
    while(true){
        int x,y;
        int c;
        c = getch();
        switch(c) {	
            case KEY_UP:
                getyx(win,y,x);
                if (y>1) {
                    y--;
                    wmove(win,y,x);
                    wrefresh(win);
                }
                break;
            case KEY_DOWN:
                getyx(win,y,x);
                if (y<N) {
                    y++;
                    wmove(win,y,x);
                    wrefresh(win);
                }
                break;
            case KEY_LEFT:
                getyx(win,y,x);
                if (x>1) {
                    x--;
                    wmove(win,y,x);
                    wrefresh(win);
                }
                break;
            case KEY_RIGHT:
                getyx(win,y,x);
                if (x<N) {
                    x++;
                    wmove(win,y,x);
                    wrefresh(win);
                }
                break;
            case 32:  //space         
            case 113: //'q'
            case 81:  //'Q'
                return c;
                break;
        }
        
    }
}

void Screen::printStatus(){
    int x,y;
    getyx(win,y,x);

    if (game.getWinner()==X){
        mvprintw(N+3,0,"X won.                     ");
    } else if (game.getWinner()==O){
        mvprintw(N+3,0,"O won.                     ");
    } else if (game.getWinner()==Draw){
        mvprintw(N+3,0,"Draw.                      ");
    } else if (game.getNext()==X){
        mvprintw(N+3,0,"Next: X.                   ");
    } else {
        mvprintw(N+3,0,"Next: O.                   ");
    }
    refresh();

    wmove(win,y,x);
    wrefresh(win);
}

void Screen::waitForQuit(){
    mvprintw(N+4,0,"Press 'q' to quit.           ");
    mvprintw(N+5,0,"                             ");
    mvprintw(N+6,0,"                             ");
    refresh();

    while(true){
        int c;
        c = getch();
        if (c==81 || c==113) {
            return;
        }
    }
}

void Screen::showWinner(){
    wattron(win,COLOR_PAIR(1) );
    std::vector<Point> winnerCells = game.getWinnerCells();
    for(Point p : winnerCells){
        wmove(win,p.y+1,p.x+1);
        int cc=winch(win);
        waddch(win,cc);
        wrefresh(win);

    }
    wattroff(win,A_BLINK);

}

void Screen::loop(){
    while (!game.ended()){
        printStatus();
        int key = getNextStep();
        if (key==81 || key==113) {
            return;
        } else if (key==32){
            int x,y;
            getyx(win,y,x);
            int cc='X';
            if (game.getNext()==O){
                cc='O';
            }
            waddch(win,cc);
            wmove(win,y,x);
            wrefresh(win);
            game.move(x-1,y-1);
        }
    }
    showWinner();
    printStatus();
    waitForQuit();    
}

Screen::~Screen(){
    delwin(win);
}

void Screen::InitNCurses(){
    initscr();
    cbreak();
    noecho();
    curs_set(1);
    keypad(stdscr, TRUE);
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
}

void Screen::DeInitNCurses(){
    endwin();
}

