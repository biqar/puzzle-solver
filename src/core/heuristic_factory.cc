//
// Created by aislam6 on 2/16/20.
//

#include "heuristic_factory.h"
#include "../8-puzzle/heuristic/hamming.cc"
#include "../8-puzzle/heuristic/manhattan.cc"
#include "../8-puzzle/heuristic/euclidean.cc"
using utils::Properties;

Heuristic *HeuristicFactory::CreateHeuristic(utils::Properties &props) {
    if (props.properties().find("heuristic") == props.properties().end()) {
        return NULL;
    }

    if (props["heuristic"] == "hamming") {
        return new Hamming();
    } else if (props["heuristic"] == "manhattan") {
        return new Manhattan();
    } else if (props["heuristic"] == "euclidean") {
        return new Euclidean();
    } else {
        return new Manhattan();
    }
}