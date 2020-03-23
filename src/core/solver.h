//
// Created by Islam, Abdullah Al Raqibul on 2/3/20.
//

#ifndef SOLVER_H
#define SOLVER_H

#include "../8-puzzle/core/state.h"
#include "heuristic.h"

class Solver {
public:
    virtual int init(void *_parameter) = 0;

    virtual int run() = 0;

    virtual void destroy() {}
};

class EightPuzzleInitParam {
public:
    State *_initial_state;
    State *_goal_state;
    Heuristic *_heuristic;
    bool _print_path;

    EightPuzzleInitParam(State *initial_state, State *goal_state, Heuristic *heuristic, bool print_path) {
        _initial_state = initial_state;
        _goal_state = goal_state;
        _heuristic = heuristic;
        _print_path = print_path;
    }
};

class NQueenInitParam {
public:
    int board_dimension;
    int mx_sideways_move;
    bool print_path;

    NQueenInitParam(int _board_dimension, int _mx_sideways_move, bool _print_path) {
        board_dimension = _board_dimension;
        mx_sideways_move = _mx_sideways_move;
        print_path = _print_path;
    }
};

#endif //SOLVER_H
