#include "screen.h"

#include <iostream>
#include <string>
#include <memory>
#include <ncurses.h>


Screen::Screen(int N):N(N){
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
    mvprintw(N+3,0,"Use arrow-keys and");
    mvprintw(N+4,0,"space-key to play.");
    mvprintw(N+5,0,"Press 'q' to quit.");
    refresh();

    //Create the play area as window
    win = newwin(N+2, N+2, 1, 2);
    box(win,0,0);
    //mvwaddch(win,3,3,'a');
    wmove(win, N/2+1, N/2+1);
    wrefresh(win);		
}

void Screen::loop(){
    bool quit = false;
    while(!quit) {	
        int x,y;
        int c;
        int cc;
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
            case 32:           
                getyx(win,y,x);
                cc = mvwinch(win,y,x);
                if (cc=='X') {
                    cc=' ';
                } else {
                    cc='X';
                }
                waddch(win,cc);
                wmove(win,y,x);
                wrefresh(win);
                break;
            case 113: //'q'
            case 81:  //'Q'
                quit = true;
                break;
        }
    }	
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
}

void Screen::DeInitNCurses(){
    endwin();
}

