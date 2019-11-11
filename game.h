#ifndef FIVE_IN_A_RAW_GAME
#define FIVE_IN_A_RAW_GAME

#include <vector>

struct Point {
    Point(int x, int y):x(x),y(y){};
    int x,y;
};

enum Value {
  None=0,
  X=1,
  O=2,
  Draw = 3  
};

class Game {
public:
  Game(int n, int wn=5);
  Value move(int x, int y);
  void unmove();
  bool check_win(int x, int y, Value curr);
  Value getValue(int x, int y);
  int size();
  bool ended();
  Value getNext();
  Value getWinner();
  std::vector<Point> getWinnerCells();

private:
  int N;
  int NN;
  int WN;
  int nr;
  std::vector<std::vector<Value>> grid;
  std::vector<Point> moves;
  Value winner; 
  Value next;

  //Auxiliary variables for storig the winner line
  int xx0, xx1, yy0, yy1; 
  int dx, dy;
};

#endif
