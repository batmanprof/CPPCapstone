#ifndef FIVE_IN_A_RAW_AI
#define FIVE_IN_A_RAW_AI

#include "game.h"
#include "random"

class AI {
public:
    virtual Point nextMove(const std::vector<std::vector<Value>> &grid, Value next) = 0;
};

class AIRandom : public AI {
public:
    AIRandom():gen(rd()){}
protected:
    std::random_device rd;  
    std::mt19937 gen;       

};

class AIRandomAll : public AIRandom {
public:
    Point nextMove(const std::vector<std::vector<Value>> &grid, Value next) override;

};

class AIRandomClose : public AIRandom {
public:
    Point nextMove(const std::vector<std::vector<Value>> &grid, Value next) override;
private:
    bool checkNeighbors(const std::vector<std::vector<Value>> &grid, int x, int y, int N);
};


#endif