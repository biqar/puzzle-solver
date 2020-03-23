//
// Created by Islam, Abdullah Al Raqibul on 3/22/20.
//

#include "core/queen.h"

class HillClimbingFCNQueens : public Solver {
public:
    HillClimbingFCNQueens(void *_parameter) {
        HillClimbingFCNQueens::init(_parameter);
    }

    int init(void *_parameter);

    int run();

    void destroy();

private:
    /* Private Data */
    int board_dimension;
    int mx_sideways_move;
    bool print_path;

    NQueenBoard *initial_state;
};

int HillClimbingFCNQueens::init(void *_parameter) {
    board_dimension = ((NQueenInitParam *)_parameter)->board_dimension;
    mx_sideways_move = ((NQueenInitParam *)_parameter)->mx_sideways_move;
    print_path = ((NQueenInitParam *)_parameter)->print_path;

    srand (time(NULL)); //initialize random seed
    initial_state = new NQueenBoard(board_dimension);
    return 1;
}

int HillClimbingFCNQueens::run() {
    return 1;
}

void HillClimbingFCNQueens::destroy() {
    //
}