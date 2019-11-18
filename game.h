#ifndef FIVE_IN_A_RAW_GAME
#define FIVE_IN_A_RAW_GAME

#include <vector>

struct Point {
public:
    Point(int x, int y):x(x),y(y){};
    Point():x(0),y(0){};
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
  Value getNext() const;
  Value getWinner() const;
  std::vector<Point> getWinnerCells();
  const std::vector<std::vector<Value>> &getGrid() const;

private:
  int N;
  int NN;
  int WN;
  std::vector<std::vector<Value>> grid;
  std::vector<Point> moves;
  Value winner; 
  Value next;

  //Auxiliary variables for storig the winner line
  int xx0, xx1, yy0, yy1; 
  int dx, dy;
};

#endif
