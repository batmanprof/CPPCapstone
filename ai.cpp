#include <iostream>

#include "ai.h"
#include "mcts.h"

Point AIRandomAll::nextMove(const Game &game){
    const std::vector<std::vector<Value>> &grid = game.getGrid();
    Value next = game.getNext();
    std::vector<Point> v;
    for(int i=0;i<grid.size();i++){
        for(int j=0;j<grid[i].size();j++){
            if (grid[i][j]==None) {
                v.push_back(Point(i,j));
            }
        }
    }    
    std::uniform_int_distribution<> dist(0, v.size()-1);
    int i=dist(gen);
    return v[i];
}

bool AIRandomClose::checkNeighbors(const std::vector<std::vector<Value>> &grid, int x, int y, int N){
    const static std::vector<int> dx = {1,1,0,-1,-1,-1, 0, 1}; //,   2,2,0,-2,-2,-2, 0, 2};
    const static std::vector<int> dy = {0,1,1, 1, 0,-1,-1,-1}; //,   0,2,2, 2, 0,-2,-2,-2};

    for(int i=0;i<dx.size();i++){
        if (x+dx[i]>=0 && x+dx[i]<N &&
            y+dy[i]>=0 && y+dy[i]<N &&
            grid[ x+dx[i] ][ y+dy[i] ]!=None) {
            return true;
        }
    }
    return false;
}

Point AIRandomClose::nextMove(const Game &game){
    const std::vector<std::vector<Value>> &grid = game.getGrid();
    Value next = game.getNext();
    std::vector<Point> v;
    int nr=0;
    for(int i=0;i<grid.size();i++){
        for(int j=0;j<grid[i].size();j++){
            if (grid[i][j]==None) {
                nr++;
                if (checkNeighbors(grid,i,j,grid.size())) {
                    v.push_back(Point(i,j));
                }
            }
        }
    }    
    if (nr==grid.size()*grid.size()) {
        return Point(grid.size()/2,grid.size()/2);
    }
    std::uniform_int_distribution<> dist(0, v.size()-1);
    int i=dist(gen);
    return v[i];    
}

Point AIMCTS::nextMove(const Game &game){
    MCTS mcts(game);
    auto p = mcts.select_move();
    return p;
}
