//
// Created by Islam, Abdullah Al Raqibul on 2/3/20.
//

#include <string>
#include <iostream>

#include "utill/properties.h"
#include "core/solver_factory.h"
#include "core/solver.h"
using namespace std;

void ParseCommandLine(int argc, const char *argv[], Properties &props);

int main(const int argc, const char *argv[]) {
    Properties props;
    ParseCommandLine(argc, argv, props);

    Solver *solver = SolverFactory::CreateSolver(props);

    return 0;
}

void ParseCommandLine(int argc, const char *argv[], Properties &props) {
    int argindex = 1;
    while (argindex < argc && StrStartWith(argv[argindex], "-")) {
        if (strcmp(argv[argindex], "-problem") == 0) {
            argindex++;
            if (argindex >= argc) {
                UsageMessage(argv[0]);
                exit(0);
            }
            props.SetProperty("puzzle", argv[argindex]);
            argindex++;
        } else if (strcmp(argv[argindex], "-algo") == 0) {
            argindex++;
            if (argindex >= argc) {
                UsageMessage(argv[0]);
                exit(0);
            }
            props.SetProperty("algorithm", argv[argindex]);
            argindex++;
        } else if (strcmp(argv[argindex], "-mode") == 0) {
            // -type is only with storedsDB, it denotes the inner data structures we will use
            argindex++;
            if (argindex >= argc) {
                UsageMessage(argv[0]);
                exit(0);
            }
            props.SetProperty("mode", argv[argindex]);
            argindex++;
        } else if (strcmp(argv[argindex], "-initial") == 0) {
            // -dbpath is only with storedsDB, it shows where the db file is
            argindex++;
            if (argindex >= argc) {
                UsageMessage(argv[0]);
                exit(0);
            }
            props.SetProperty("initial_state", argv[argindex]);
            argindex++;
        } else if (strcmp(argv[argindex], "-goal") == 0) {
            argindex++;
            if (argindex >= argc) {
                UsageMessage(argv[0]);
                exit(0);
            }
            props.SetProperty("goal_state", argv[argindex]);
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