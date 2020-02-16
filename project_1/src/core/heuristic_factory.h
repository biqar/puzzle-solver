//
// Created by aislam6 on 2/16/20.
//

#ifndef HEURISTIC_FACTORY_H
#define HEURISTIC_FACTORY_H

#include "heuristic.h"
using utils::Properties;

class HeuristicFactory {
public:
    static Heuristic *CreateHeuristic(utils::Properties &props);
};

#endif //HEURISTIC_FACTORY_H
