//
// Created by Islam, Abdullah Al Raqibul on 3/22/20.
//

#include "core/board.h"

class HillClimbingWSideWaysNQueens : public Solver {
public:
    HillClimbingWSideWaysNQueens(State *_initial_state, State *_goal_state, Heuristic *_heuristic, bool _print_path) {
        HillClimbingWSideWaysNQueens::init(_initial_state, _goal_state, _heuristic, _print_path);
    }

    int init(State *_initial_state, State *_goal_state, Heuristic *_heuristic, bool _print_path);

    int run();

    void destroy();

private:
    /* Private Data */
};

int HillClimbingWSideWaysNQueens::init(State *_initial_state, State *_goal_state, Heuristic *_heuristic, bool _print_path) {
    return 1;
}

int HillClimbingWSideWaysNQueens::run() {
    return 1;
}

void HillClimbingWSideWaysNQueens::destroy() {
    //
}