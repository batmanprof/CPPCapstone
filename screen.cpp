#include "screen.h"

#include <iostream>
#include <string>
#include <memory>
#include <ncurses.h>


Screen::Screen(Game &igame):game(igame),N(igame.size()){
    int c;

    clear();
    mvprintw(0,0,"Select X player:");
    mvprintw(1,0,"1 - Human");
    mvprintw(2,0,"2 - AI (Random)");
    mvprintw(3,0,"3 - AI (RandomClose)");
    mvprintw(4,0,"4 - AI (MCTS)");
    move(5, 0);
    refresh();
    while (true){
        c = getch();
        if (c=='1' || c=='2' || c=='3' || c=='4') {
            break;
        }
    }
    if (c=='2') {
        aiX = std::make_unique<AIRandomAll>();
    } else if (c=='3') {
        aiX = std::make_unique<AIRandomClose>();
    } else if (c=='4') {
        aiX = std::make_unique<AIMCTS>();
    }

    mvprintw(5,0,"Select O player:");
    mvprintw(6,0,"1 - Human");
    mvprintw(7,0,"2 - AI (Random)");
    mvprintw(8,0,"3 - AI (RandomClose)");
    mvprintw(9,0,"4 - AI (MCTS)");
    move(10, 0);
    refresh();
    while (true){
        c = getch();
        if (c=='1' || c=='2' || c=='3' || c=='4') {
            break;
        }
    }
    if (c=='2') {
        aiO = std::make_unique<AIRandomAll>();
    } else if (c=='3') {
        aiO = std::make_unique<AIRandomClose>();
    } else if (c=='4') {
        aiO = std::make_unique<AIMCTS>();
    }


    clear();
    refresh();

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
    move(0,0);
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

bool Screen::processPlayerStep(){
    while (true) {
        int key = getNextStep();
        if (key==81 || key==113) {
            return true;
        } else if (key==32){
            int x,y;
            getyx(win,y,x);
            if (game.getValue(x-1,y-1)!=None) {
                continue;
            }
            int cc='X';
            if (game.getNext()==O){
                cc='O';
            }
            waddch(win,cc);
            wmove(win,y,x);
            wrefresh(win);
            game.move(x-1,y-1);
            break;
        }
    }
    return false;
}

void Screen::processAIStep(int x, int y){
    int cc='X';
    if (game.getNext()==O){
        cc='O';
    }
    wmove(win,y+1,x+1);
    waddch(win,cc);
    wmove(win,y+1,x+1);
    wrefresh(win);
    game.move(x,y);
}

void Screen::screenLogic(){
    while (!game.ended()){
        printStatus();
        if (game.getNext()==X && aiX) {
            Point p = aiX->nextMove(game);
            processAIStep(p.x,p.y);
        } else if (game.getNext()==O && aiO) {
            Point p = aiO->nextMove(game);
            processAIStep(p.x,p.y);
        } else {
            bool exit = processPlayerStep();
            if (exit) {
                return;
            }
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

