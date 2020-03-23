//
// Created by aislam6 on 2/16/20.
//

#ifndef HEURISTIC_H
#define HEURISTIC_H

#include "../8-puzzle/core/state.h"

class Heuristic {
public:
    virtual int guess_distance(void *_parameter) = 0;
};

class EightPuzzleHeuristicParam {
public:
    State *current_state;
    State *goal_state;

    EightPuzzleHeuristicParam(State *_current_state, State *_goal_state) {
        current_state = _current_state;
        goal_state = _goal_state;
    }
};

#endif //HEURISTIC_H
