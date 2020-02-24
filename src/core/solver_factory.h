//
// Created by Islam, Abdullah Al Raqibul on 2/3/20.
//

#ifndef SOLVER_FACTORY_H
#define SOLVER_FACTORY_H

#include "solver.h"
#include "heuristic.h"
using utils::Properties;

class SolverFactory {
public:
    static Solver *CreateSolver(utils::Properties &props, Heuristic *_heuristic);
};

#endif //SOLVER_FACTORY_H
