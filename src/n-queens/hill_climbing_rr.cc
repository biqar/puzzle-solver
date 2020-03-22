//
// Created by Islam, Abdullah Al Raqibul on 3/22/20.
//

#include "core/board.h"

class HillClimbingRRNQueens : public Solver {
public:
    HillClimbingRRNQueens(State *_initial_state, State *_goal_state, Heuristic *_heuristic, bool _print_path) {
        HillClimbingRRNQueens::init(_initial_state, _goal_state, _heuristic, _print_path);
    }

    int init(State *_initial_state, State *_goal_state, Heuristic *_heuristic, bool _print_path);

    int run();

    void destroy();

private:
    /* Private Data */
};

int HillClimbingRRNQueens::init(State *_initial_state, State *_goal_state, Heuristic *_heuristic, bool _print_path) {
    return 1;
}

int HillClimbingRRNQueens::run() {
    return 1;
}

void HillClimbingRRNQueens::destroy() {
    //
}