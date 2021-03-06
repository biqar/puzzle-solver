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

class MapColoringInitParam {
public:
    string file_name_;
    int max_colors_;
    bool print_graph_;
    bool try_mrv_;
    bool try_degree_c_;
    bool try_lcv_;

    MapColoringInitParam(string file_name, int max_colors, bool print_graph, bool mrv, bool degree_heu, bool lcv) {
        file_name_ = file_name;
        max_colors_ = max_colors;
        print_graph_ = print_graph;
        try_mrv_ = mrv;
        try_degree_c_ = degree_heu;
        try_lcv_ = lcv;
    }
};

#endif //SOLVER_H
