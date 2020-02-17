//
// Created by aislam6 on 2/16/20.
//

#include "heuristic_factory.h"
#include "../heuristic/hamming.cc"
#include "../heuristic/manhattan.cc"
#include "../heuristic/euclidean.cc"
using utils::Properties;

Heuristic *HeuristicFactory::CreateHeuristic(utils::Properties &props) {
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