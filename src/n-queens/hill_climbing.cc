//
// Created by Islam, Abdullah Al Raqibul on 3/22/20.
//

#include "core/queen.h"
#include "core/board.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

class HillClimbingNQueens : public Solver {
public:
    HillClimbingNQueens(void *_parameter) {
        HillClimbingNQueens::init(_parameter);
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

int HillClimbingNQueens::init(void *_parameter) {
    board_dimension = ((NQueenInitParam *)_parameter)->board_dimension;
    mx_sideways_move = ((NQueenInitParam *)_parameter)->mx_sideways_move;
    print_path = ((NQueenInitParam *)_parameter)->print_path;

    srand (time(NULL)); //initialize random seed
    initial_state = new NQueenBoard(board_dimension);
    initial_state->print_queens();
    return 1;
}

int HillClimbingNQueens::run() {
    NQueenBoard next = NULL;
    NQueenBoard current = *initial_state;
    int iteration = 0;
    int current_attack = current.calculate_attack(), next_attack;

    while(true) {
        iteration += 1;
        next = current.best_successor();
        next_attack = next.calculate_attack();

        //printf("current attack: %d, next attack: %d\n", current_attack, next_attack);
        if(next_attack == 0) {
            printf("[success] %d\n", iteration);
            return 1;
        }
        else if(current_attack > next_attack) {
            current = next;
            current_attack = next_attack;
        }
        else if(current_attack <= next_attack) {
            printf("[failure] %d\n", iteration);
            return 0;
        }
    }
}

void HillClimbingNQueens::destroy() {
    free(initial_state);
}