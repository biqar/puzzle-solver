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

#include "../n-queens/hill_climbing.cc"
#include "../n-queens/hill_climbing_random_best.cc"
#include "../n-queens/hill_climbing_stochastic.cc"
#include "../n-queens/hill_climbing_fc.cc"
#include "../n-queens/hill_climbing_sways_move.cc"
#include "../n-queens/hill_climbing_rr.cc"
#include "../n-queens/hill_climbing_rr_sways_move.cc"

using utils::Properties;

Solver *SolverFactory::CreateSolver(utils::Properties &props, Heuristic *_heuristic) {
    if (props["puzzle"] == "8-puzzle") {
        if(props["algorithm"] == "a_star") {
            return new AStarEightPuzzle(new EightPuzzleInitParam(construct_state(props["initial_state"]), construct_state(props["goal_state"]), _heuristic, utils::to_bool(props["print_path"])));
        }
        if(props["algorithm"] == "ida_star") {
            return new IdaStarEightPuzzle(new EightPuzzleInitParam(construct_state(props["initial_state"]), construct_state(props["goal_state"]), _heuristic, utils::to_bool(props["print_path"])));
        }
        if(props["algorithm"] == "bfs") {
            if(props["mode"] == "bi-directional") {
                return new BfsBidirEightPuzzle(new EightPuzzleInitParam(construct_state(props["initial_state"]), construct_state(props["goal_state"]), _heuristic, utils::to_bool(props["print_path"])));
            }
            if(props["mode"] == "greedy") {
                return new BfsGreedyEightPuzzle(new EightPuzzleInitParam(construct_state(props["initial_state"]), construct_state(props["goal_state"]), _heuristic, utils::to_bool(props["print_path"])));
            }
            if(props["mode"] == "optimized") {
                return new BfsOptEightPuzzle(new EightPuzzleInitParam(construct_state(props["initial_state"]), construct_state(props["goal_state"]), _heuristic, utils::to_bool(props["print_path"])));
            }
            return new BfsEightPuzzle(new EightPuzzleInitParam(construct_state(props["initial_state"]), construct_state(props["goal_state"]), _heuristic, utils::to_bool(props["print_path"])));
        }
        if(props["algorithm"] == "dfs") {
            if(props["mode"] == "recursive") {
                return new DfsRecursivEightPuzzle(new EightPuzzleInitParam(construct_state(props["initial_state"]), construct_state(props["goal_state"]), _heuristic, utils::to_bool(props["print_path"])));
            }
            if(props["mode"] == "stack-based") {
                return new DfsStackEightPuzzle(new EightPuzzleInitParam(construct_state(props["initial_state"]), construct_state(props["goal_state"]), _heuristic, utils::to_bool(props["print_path"])));
            }
            return NULL;
        }
        if(props["algorithm"] == "dls") {
            if(props["mode"] == "bi-directional") {
                return new DlsBidirEightPuzzle(new EightPuzzleInitParam(construct_state(props["initial_state"]), construct_state(props["goal_state"]), _heuristic, utils::to_bool(props["print_path"])));
            }
            return new DlsEightPuzzle(new EightPuzzleInitParam(construct_state(props["initial_state"]), construct_state(props["goal_state"]), _heuristic, utils::to_bool(props["print_path"])));
        }
        if(props["algorithm"] == "ids") {
            if(props["mode"] == "bi-directional") {
                return new IdsBidirEightPuzzle(new EightPuzzleInitParam(construct_state(props["initial_state"]), construct_state(props["goal_state"]), _heuristic, utils::to_bool(props["print_path"])));
            }
            return new IdsEightPuzzle(new EightPuzzleInitParam(construct_state(props["initial_state"]), construct_state(props["goal_state"]), _heuristic, utils::to_bool(props["print_path"])));
        }
        return NULL;
    }
    else if (props["puzzle"] == "n-queen") {
        if(props["algorithm"] == "hill-climbing") {
            if(props["mode"] == "random-best") {
                return new HillClimbingRandBestNQueens(new NQueenInitParam(std::stoi(props["dim"]), std::stoi(props["mx_sways_move"]), utils::to_bool(props["print_path"])));
            }
            if(props["mode"] == "first-choice") {
                return new HillClimbingFCNQueens(new NQueenInitParam(std::stoi(props["dim"]), std::stoi(props["mx_sways_move"]), utils::to_bool(props["print_path"])));
            }
            if(props["mode"] == "stochastic") {
                return new HillClimbingStochasticNQueens(new NQueenInitParam(std::stoi(props["dim"]), std::stoi(props["mx_sways_move"]), utils::to_bool(props["print_path"])));
            }
            if(props["mode"] == "sideways-move") {
                return new HillClimbingWSideWaysNQueens(new NQueenInitParam(std::stoi(props["dim"]), std::stoi(props["mx_sways_move"]), utils::to_bool(props["print_path"])));
            }
            if(props["mode"] == "random-restart") {
                return new HillClimbingRRNQueens(new NQueenInitParam(std::stoi(props["dim"]), std::stoi(props["mx_sways_move"]), utils::to_bool(props["print_path"])));
            }
            if(props["mode"] == "random-restart-sways-move") {
                return new HillClimbingRRWSideWaysNQueens(new NQueenInitParam(std::stoi(props["dim"]), std::stoi(props["mx_sways_move"]), utils::to_bool(props["print_path"])));
            }
            return new HillClimbingNQueens(new NQueenInitParam(std::stoi(props["dim"]), std::stoi(props["mx_sways_move"]), utils::to_bool(props["print_path"])));
        }
        return NULL;
    }
    else {
        return NULL;
    }
}