#ifndef FIVE_IN_A_RAW_MCTS
#define FIVE_IN_A_RAW_MCTS

#include <memory>
#include <vector>
#include <random>

#include "game.h"
#include "params.h"

struct Edge;

struct Node {
    Node():edges(0){}
    std::vector<std::unique_ptr<Edge>> edges;
};

struct Edge {

    Edge(int x, int y, std::unique_ptr<Node> node=nullptr):
      N(0.0),W(0.0),Q(0.0),
      act_x(x),act_y(y),
      result_node(std::move(node)) {}


    double N;
    double W;
    double Q;
    int act_x;
    int act_y;

    std::unique_ptr<Node> result_node;
};

class MCTS {
public:
    MCTS(const Game &game, std::unique_ptr<Node> i_root_node=nullptr, double MCTS_U_COEFF = prm::MCTS_U_COEFF);

    Point select_move(bool competitive=true, int nr=prm::MCTS_NR);

private:
    int N; //Number of simulations
    std::unique_ptr<Node> root_node;
    Game game;
    std::random_device rd;
    std::mt19937 gen;

    const double MCTS_U_COEFF;

    void extend_update();
    double estimate_value();
    void extend_graph(Node *curr);
};

#endif