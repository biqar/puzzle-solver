//
// Created by Islam, Abdullah Al Raqibul on 2/3/20.
//

#ifndef SOLVER_H
#define SOLVER_H

#include "state.h"

class Solver {
public:
    virtual int init(State *_initial_state, State *_goal_state) = 0;

    virtual int run() = 0;

    virtual void destroy() {}
};

#endif //SOLVER_H