#include <cmath>

#include "mcts.h"
#include "ai.h"


MCTS::MCTS(const Game &game, std::unique_ptr<Node> root_node,double MCTS_U_COEFF)
:game(game), root_node(std::move(root_node)),MCTS_U_COEFF(MCTS_U_COEFF),gen(),N(0) {
    if (root_node==nullptr) {
        root_node = std::make_unique<Node>();
    }
}

Point MCTS::select_move(bool competitive, int nr){
    for(int i=0;i<nr;++i){
        extend_update();
    }
    if (competitive){
        std::vector<Point> bests;
        int maxN=-1;
        for(auto &e:root_node->edges){
            if (e->N>maxN){
                maxN=e->N;
                bests.clear();
                bests.emplace_back(Point(e->act_x, e->act_y));
            } else if (e->N==maxN){
                bests.emplace_back(Point(e->act_x, e->act_y));
            }
        }

        std::uniform_int_distribution<int> rnd(0,bests.size());
        int index = rnd(gen);
        return bests[index];
    } else {
    }
    return Point();

}
void MCTS::extend_update(){
    Node *curr = root_node.get();
    std::vector<Edge*> route;
    std::vector<double> probs;
    int parentN=N;

    //Finding a leaf node to extend
    while(curr->edges.size()!=0){
        probs.clear();
        for(auto &e:curr->edges){
            float Q = e->Q;
            float U = MCTS_U_COEFF * std::sqrt(std::log(parentN)/(double)(e->N));
            probs.emplace_back(Q + U);
        }
        std::discrete_distribution<int> dist(probs.begin(), probs.end());
        int index = dist(gen);
        Edge *e = curr->edges[index].get();
        parentN=e->N;
        route.push_back(e);
        curr = e->result_node.get();
        game.move(e->act_x, e->act_y);        
    }

    //In MTCS we use value 1.0 if the next player will win in 100%
    //and 0.0 if the next player will win in 0% (i.e. they [he or she] will lose)
    //So the value depend on the fact who is the next player
    int winner = game.getWinner();
    double value;
    if (winner == X or winner == O) {
        value = 1.0;         //From the perspective of the player who has just played
    } else if (winner == Draw) { 
        value = 0.5;            //From the perspective of the player who has just played
    } else {  //Not terminating state
        //Estimating value (e.g with random play)
        value=estimate_value();
        if (game.getNext()==O){
            value = 1.0 - value;
        }
        //Extending the graph
        extend_graph(curr);
    }

    //Update egdes back toward the root
    for(int i=route.size()-1;i>=0;--i){
        route[i]->N++;
        route[i]->W += value;
        route[i]->Q = route[i]->W / route[i]->N;
        value=1.0-value;
        game.unmove();
    }
    N++;
}

double MCTS::estimate_value(){
    AIRandomAll rndai;
    Point p; 
    int move_nr=0;

    while(game.getWinner()==None){
        p=rndai.nextMove(game.getGrid(), game.getNext());
        game.move(p.x,p.y);
        move_nr++;
    }

    Value winner=game.getWinner();

    for(int i=0;i<move_nr;++i){
        game.unmove();
    }

    if (winner==X) {
        return 1.0;
    } else if (winner==O) {
        return 0.0;
    } else {
        return Draw;
    }
}


void MCTS::extend_graph(Node *curr){
    for(int x=0;x<game.size();++x) {
        for(int y=0;y<game.size();++y) {
            if (game.getValue(x,y) == None){
                std::unique_ptr<Node> n=std::make_unique<Node>(); 
                curr->edges.emplace_back(new Edge(x,y,std::move(n)));
            }
        }
    }
}
