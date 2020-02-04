//
// Created by Islam, Abdullah Al Raqibul on 2/3/20.
//

#ifndef SOLVER_FACTORY_H
#define SOLVER_FACTORY_H

#include "solver.h"
#include "../utill/properties.h"

class SolverFactory {
public:
    static Solver *CreateSolver(Properties &props);
};

#endif //SOLVER_FACTORY_H
