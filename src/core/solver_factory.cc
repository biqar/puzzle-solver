//
// Created by Islam, Abdullah Al Raqibul on 2/3/20.
//

#include "solver_factory.h"
#include "heuristic.h"
#include "../8-puzzle/a_star.cc"
#include "../8-puzzle/ida_star.cc"
#include "../8-puzzle/bfs.cc"
#include "../8-puzzle/bfs_opt.cc"
#include "../8-puzzle/bfs_bidir.cc"
#include "../8-puzzle/bfs_greedy.cc"
#include "../8-puzzle/dfs_recursive.cc"
#include "../8-puzzle/dfs_stack.cc"
#include "../8-puzzle/dls.cc"
#include "../8-puzzle/dls_bidir.cc"
#include "../8-puzzle/ids.cc"
#include "../8-puzzle/ids_bidir.cc"

using utils::Properties;

Solver *SolverFactory::CreateSolver(utils::Properties &props, Heuristic *_heuristic) {
    if (props["puzzle"] == "8-puzzle") {
        if(props["algorithm"] == "a_star") {
            return new AStarEightPuzzle(construct_state(props["initial_state"]), construct_state(props["goal_state"]), _heuristic, utils::to_bool(props["print_path"]));
        }
        if(props["algorithm"] == "ida_star") {
            return new IdaStarEightPuzzle(construct_state(props["initial_state"]), construct_state(props["goal_state"]), _heuristic, utils::to_bool(props["print_path"]));
        }
        if(props["algorithm"] == "bfs") {
            if(props["mode"] == "bi-directional") {
                return new BfsBidirEightPuzzle(construct_state(props["initial_state"]), construct_state(props["goal_state"]), _heuristic, utils::to_bool(props["print_path"]));
            }
            if(props["mode"] == "greedy") {
                return new BfsGreedyEightPuzzle(construct_state(props["initial_state"]), construct_state(props["goal_state"]), _heuristic, utils::to_bool(props["print_path"]));
            }
            if(props["mode"] == "optimized") {
                return new BfsOptEightPuzzle(construct_state(props["initial_state"]), construct_state(props["goal_state"]), _heuristic, utils::to_bool(props["print_path"]));
            }
            return new BfsEightPuzzle(construct_state(props["initial_state"]), construct_state(props["goal_state"]), _heuristic, utils::to_bool(props["print_path"]));
        }
        if(props["algorithm"] == "dfs") {
            if(props["mode"] == "recursive") {
                return new DfsRecursivEightPuzzle(construct_state(props["initial_state"]), construct_state(props["goal_state"]), _heuristic, utils::to_bool(props["print_path"]));
            }
            if(props["mode"] == "stack-based") {
                return new DfsStackEightPuzzle(construct_state(props["initial_state"]), construct_state(props["goal_state"]), _heuristic, utils::to_bool(props["print_path"]));
            }
            return NULL;
        }
        if(props["algorithm"] == "dls") {
            if(props["mode"] == "bi-directional") {
                return new DlsBidirEightPuzzle(construct_state(props["initial_state"]), construct_state(props["goal_state"]), _heuristic, utils::to_bool(props["print_path"]));
            }
            return new DlsEightPuzzle(construct_state(props["initial_state"]), construct_state(props["goal_state"]), _heuristic, utils::to_bool(props["print_path"]));
        }
        if(props["algorithm"] == "ids") {
            if(props["mode"] == "bi-directional") {
                return new IdsBidirEightPuzzle(construct_state(props["initial_state"]), construct_state(props["goal_state"]), _heuristic, utils::to_bool(props["print_path"]));
            }
            return new IdsEightPuzzle(construct_state(props["initial_state"]), construct_state(props["goal_state"]), _heuristic, utils::to_bool(props["print_path"]));
        }
        return NULL;
    } else {
        return NULL;
    }
}