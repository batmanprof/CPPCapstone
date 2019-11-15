#ifndef FIVE_IN_A_RAW_MCTS
#define FIVE_IN_A_RAW_MCTS

#include <memory>
#include <vector>
#include <random>

#include "game.h"
#include "params.h"

struct Edge;

struct Node {
    std::vector<std::unique_ptr<Edge>> edges;
};

struct Edge {

    Edge(int x, int y, std::unique_ptr<Node> node=nullptr):
      N(0),W(0.0),Q(0.0),
      act_x(x),act_y(y),
      result_node(std::move(node)) {}


    int N;
    double W;
    double Q;
    int act_x;
    int act_y;

    std::unique_ptr<Node> result_node;
};

class MCTS {
public:
    MCTS(const Game &game, std::unique_ptr<Node> root_node=nullptr, double MCTS_U_COEFF = prm::MCTS_U_COEFF);

    Point select_move(bool competitive=true, int nr=prm::MCTS_NR);
    void extend_update();

private:
    int N; //Number of simulations
    std::unique_ptr<Node> root_node;
    Game game;
    std::default_random_engine gen;

    const double MCTS_U_COEFF;

    double estimate_value();
    void extend_graph(Node *curr);
};

#endif