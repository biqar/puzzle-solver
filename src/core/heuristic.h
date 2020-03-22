//
// Created by aislam6 on 2/16/20.
//

#ifndef HEURISTIC_H
#define HEURISTIC_H

#include "../8-puzzle/core/state.h"

class Heuristic {
public:
    virtual int guess_distance(State *_current_state, State *_goal_state) = 0;
};

#endif //HEURISTIC_H
