//
// Created by Islam, Abdullah Al Raqibul on 2/3/20.
//

#include "solver_factory.h"
#include "../8-puzzle/a_star.cc"
#include "../8-puzzle/ida_star.cc"
#include "../8-puzzle/bfs.cc"
#include "../8-puzzle/bfs_bidir.cc"
#include "../8-puzzle/bfs_greedy.cc"

using utils::Properties;

Solver *SolverFactory::CreateSolver(utils::Properties &props) {
    if (props["puzzle"] == "8-puzzle") {
        if(props["algorithm"] == "a_star") {
            return new AStarEightPuzzle(construct_initial_state(), construct_goal_state());
        }
        if(props["algorithm"] == "ida_star") {
            return new IdaStarEightPuzzle(construct_initial_state(), construct_goal_state());
        }
        if(props["algorithm"] == "bfs") {
            if(props["mode"] == "bi-directional") {
                return new BfsBidirEightPuzzle(construct_initial_state(), construct_goal_state());
            }
            if(props["mode"] == "greedy") {
                return new BfsGreedyEightPuzzle(construct_initial_state(), construct_goal_state());
            }
            return new BfsEightPuzzle(construct_initial_state(), construct_goal_state());
        }
        if(props["algorithm"] == "dfs") {
            if(props["mode"] == "recursive") {
                //return new StoredsDB();
            }
            if(props["mode"] == "stack-based") {
                //return new StoredsDB();
            }
            return NULL;
        }
        if(props["algorithm"] == "dls") {
            if(props["mode"] == "bi-directional") {
                //return new StoredsDB();
            }
            //return new StoredsDB();
        }
        if(props["algorithm"] == "ids") {
            if(props["mode"] == "bi-directional") {
                //return new StoredsDB();
            }
            //return new StoredsDB();
        }
        return NULL;
    } else {
        return NULL;
    }
}