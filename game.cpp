#include "game.h"

#include <cassert>
#include <iostream>

Game::Game(int n, int wn):
  N(n),
  NN(n*n),
  WN(wn),
  grid( std::vector<std::vector<Value>>(n,std::vector<Value>(n,None)) ),
  moves( std::vector<Point>()),
  winner(None),
  next(X)
  {}

Value Game::move(int x, int y){
    assert(x>=0 && x<N);       //ERROR: Wrong x value.
    assert(y>=0 && y<N);       //ERROR: Wrong y value.
    assert(winner==0);         //ERROR: The game has already ended.
    assert(grid[x][y]==None);  //ERROR: The square is already occupied.
    grid[x][y]=next;
    moves.push_back(Point(x,y));
    if (check_win(x,y,next)) {
        winner=next;
    } else if (moves.size()==NN){
        winner=Draw;
    }
    next = (next==X?O:X);
    return winner;
}

void Game::unmove(){
    assert(moves.size()>0); //ERROR: Game not started, no move to undo.
    Point p=moves.back();
    grid[p.x][p.y]=None;
    moves.resize(moves.size()-1);
    winner=None;
    next = (next==X?O:X);
}

bool Game::check_win(int x, int y, Value curr){
    int l;

    //horizontal
    l=1;
    xx0=x;
    yy0=y;
    while(l<WN && xx0-1>=0 && grid[xx0-1][yy0]==curr){
        xx0--;
        l++;
    }
    xx1=x;
    yy1=y;
    while(l<WN && xx1+1<N && grid[xx1+1][yy1]==curr){
        xx1++;
        l++;
    }
    if (l>=WN) {
        dx=1;
        dy=0;
        return true;
    }

    //vertical
    l=1;
    xx0=x;
    yy0=y;
    while(l<WN && yy0-1>=0 && grid[xx0][yy0-1]==curr){
        yy0--;
        l++;
    }
    xx1=x;
    yy1=y;
    while(l<WN && yy1+1<N && grid[xx1][yy1+1]==curr){
        yy1++;
        l++;
    }
    if (l>=WN) {
        dx=0;
        dy=1;
        return true;
    }

    //diag: "\"
    l=1;
    xx0=x;
    yy0=y;
    while(l<WN && xx0-1>=0 && yy0-1>=0 && grid[xx0-1][yy0-1]==curr){
        xx0--;
        yy0--;
        l++;
    }
    xx1=x;
    yy1=y;
    while(l<WN && xx1+1<N && yy1+1<N && grid[xx1+1][yy1+1]==curr){
        xx1++;
        yy1++;
        l++;
    }
    if (l>=WN) {
        dx=1;
        dy=1;
        return true;
    }

    //diag: "/"
    l=1;
    xx0=x;
    yy0=y;
    while(l<WN && xx0-1>=0 && yy0+1<N && grid[xx0-1][yy0+1]==curr){
        xx0--;
        yy0++;
        l++;
    }
    xx1=x;
    yy1=y;
    while(l<WN && xx1+1<N && yy1-1>=0 && grid[xx1+1][yy1-1]==curr){
        xx1++;
        yy1--;
        l++;
    }
    if (l>=WN) {
        dx=1;
        dy=-1;
        return true;
    }

    return false;
}

Value Game::getValue(int x, int y){
    assert(x>=0 && x<N);       //ERROR: Wrong x value.
    assert(y>=0 && y<N);       //ERROR: Wrong y value.
    return grid[x][y];
}

int Game::size(){
    return N;
}

bool Game::ended(){
    return winner!=None; 
}

Value Game::getNext() const {
    return next;
}

Value Game::getWinner() const {
    return winner;
}

std::vector<Point> Game::getWinnerCells(){
    assert(winner!=0); //ERROR: The game is not ended yet.
    int x,y;
    std::vector<Point> res;
    for(x=xx0, y=yy0;x!=xx1 || y!=yy1; x+=dx, y+=dy){
        res.push_back(Point(x,y));
    }
    res.push_back(Point(x,y));
    return res;
}

const std::vector<std::vector<Value>> &Game::getGrid() const {
    return grid;
}
