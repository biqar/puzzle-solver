//
// Created by Islam, Abdullah Al Raqibul on 2/3/20.
//

#include <string>
#include <iostream>
#include "core/solver.h"
#include "core/heuristic.h"
#include "core/solver_factory.h"
#include "core/heuristic_factory.h"

using utils::Properties;
using namespace std;

void ParseCommandLine(int argc, const char *argv[], utils::Properties &props);
void UsageMessage(const char *command);
bool StrStartWith(const char *str, const char *pre);

int main(const int argc, const char *argv[]) {
    utils::Properties props;
    ParseCommandLine(argc, argv, props);

    Heuristic *_heuristic = HeuristicFactory::CreateHeuristic(props);
    Solver *solver = SolverFactory::CreateSolver(props, _heuristic);
    solver->run();
    solver->destroy();

    return 0;
}

void ParseCommandLine(int argc, const char *argv[], utils::Properties &props) {
    int argindex = 1;
    while (argindex < argc && StrStartWith(argv[argindex], "-")) {
        if (strcmp(argv[argindex], "-problem") == 0) {
            // it denotes the puzzle name we will solve
            argindex++;
            if (argindex >= argc) {
                UsageMessage(argv[0]);
                exit(0);
            }
            props.SetProperty("puzzle", argv[argindex]);
            argindex++;
        } else if (strcmp(argv[argindex], "-algo") == 0) {
            // it denotes the algorithm strategy we will use
            argindex++;
            if (argindex >= argc) {
                UsageMessage(argv[0]);
                exit(0);
            }
            props.SetProperty("algorithm", argv[argindex]);
            argindex++;
        } else if (strcmp(argv[argindex], "-mode") == 0) {
            // it denotes the inner methodology we will use
            argindex++;
            if (argindex >= argc) {
                UsageMessage(argv[0]);
                exit(0);
            }
            props.SetProperty("mode", argv[argindex]);
            argindex++;
        } else if (strcmp(argv[argindex], "-heu") == 0) {
            // it denotes the heuristic method that the algorithm will use
            argindex++;
            if (argindex >= argc) {
                UsageMessage(argv[0]);
                exit(0);
            }
            props.SetProperty("heuristic", argv[argindex]);
            argindex++;
        } else if (strcmp(argv[argindex], "-initial") == 0) {
            // it denotes the initial board configuration
            argindex++;
            if (argindex >= argc) {
                UsageMessage(argv[0]);
                exit(0);
            }
            props.SetProperty("initial_state", argv[argindex]);
            argindex++;
        } else if (strcmp(argv[argindex], "-goal") == 0) {
            // it denotes the goal state of the board
            argindex++;
            if (argindex >= argc) {
                UsageMessage(argv[0]);
                exit(0);
            }
            props.SetProperty("goal_state", argv[argindex]);
            argindex++;
        } else if (strcmp(argv[argindex], "-board_dim") == 0) {
            // it denotes the goal state of the board
            argindex++;
            if (argindex >= argc) {
                UsageMessage(argv[0]);
                exit(0);
            }
            props.SetProperty("dim", argv[argindex]);
            argindex++;
        } else if (strcmp(argv[argindex], "-mx_sideways_move") == 0) {
            // it denotes the goal state of the board
            argindex++;
            if (argindex >= argc) {
                UsageMessage(argv[0]);
                exit(0);
            }
            props.SetProperty("mx_sways_move", argv[argindex]);
            argindex++;
        } else if (strcmp(argv[argindex], "-file") == 0) {
            // it denotes the goal state of the board
            argindex++;
            if (argindex >= argc) {
                UsageMessage(argv[0]);
                exit(0);
            }
            props.SetProperty("filename", argv[argindex]);
            argindex++;
        } else if (strcmp(argv[argindex], "-mcolor") == 0) {
            // it denotes the goal state of the board
            argindex++;
            if (argindex >= argc) {
                UsageMessage(argv[0]);
                exit(0);
            }
            props.SetProperty("mx_colors", argv[argindex]);
            argindex++;
        } else if (strcmp(argv[argindex], "-print_path") == 0) {
            // flag denotes if you like to print the path after reaching goal
            argindex++;
            if (argindex >= argc) {
                UsageMessage(argv[0]);
                exit(0);
            }
            props.SetProperty("print_path", argv[argindex]);
            argindex++;
        } else {
            cout << "Unknown option '" << argv[argindex] << "'" << endl;
            exit(0);
        }
    }

    if (argindex == 1 || argindex != argc) {
        UsageMessage(argv[0]);
        exit(0);
    }
}

void UsageMessage(const char *command) {
    cout << "Usage: " << command << " [options]" << endl;
    cout << "Options:" << endl;
    cout << "  -problem puzzle-name: specify the puzzle name to solve" << endl;
    cout << "  -algo search-strategy: specify the search strategy to solve the puzzle" << endl;
    cout << "  -mode inner-methodology: specify the inner methodology for the search strategy" << endl;
    cout << "  -heuristic heuristic-function: specify the heuristic function you want to use, [default: manhattan]" << endl;
    cout << "  -initial initial-board-setup: specify the initial board setup for your puzzle" << endl;
    cout << "  -goal goal-state: specify the goal state of your puzzle" << endl;
    cout << "  -print_path print-flag: Flag to indicate printing path if solution exist, accepts boolean string (i.e. true or false)." << endl;
}

inline bool StrStartWith(const char *str, const char *pre) {
    return strncmp(str, pre, strlen(pre)) == 0;
}