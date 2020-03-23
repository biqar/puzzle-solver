//
// Created by Islam, Abdullah Al Raqibul on 3/22/20.
//

#include "core/queen.h"

class HillClimbingRRWSideWaysNQueens : public Solver {
public:
    HillClimbingRRWSideWaysNQueens(void *_parameter) {
        HillClimbingRRWSideWaysNQueens::init(_parameter);
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

int HillClimbingRRWSideWaysNQueens::init(void *_parameter) {
    board_dimension = ((NQueenInitParam *)_parameter)->board_dimension;
    mx_sideways_move = ((NQueenInitParam *)_parameter)->mx_sideways_move;
    print_path = ((NQueenInitParam *)_parameter)->print_path;

    srand (time(NULL)); //initialize random seed
    initial_state = new NQueenBoard(board_dimension);
    return 1;
}

int HillClimbingRRWSideWaysNQueens::run() {
    NQueenBoard next = NULL;
    NQueenBoard current = *initial_state;
    int iteration = 0;
    int sideways_move = 0;
    int restart = 0;
    int current_attack = current.calculate_attack(), next_attack;

    while(true) {
        iteration += 1;
        next = current.best_successor();
        next_attack = next.calculate_attack();

        //printf("current attack: %d, next attack: %d\n", current_attack, next_attack);
        if(next_attack == 0) {
            printf("[success] step: %d, restart: %d\n", iteration, restart);
            return 1;
        }
        else if(current_attack > next_attack) {
            sideways_move = 0;
            current = next;
            current_attack = next_attack;
        }
        else if(current_attack == next_attack) {    //sideways walk
            sideways_move += 1;
            current = next;

            if(sideways_move > mx_sideways_move) {
                printf("[failure] %d\n", iteration);
                restart += 1;
                current = *(new NQueenBoard(board_dimension));
                current_attack = current.calculate_attack();
            }
        }
        else {
            printf("[failure] %d\n", iteration);
            restart += 1;
            current = *(new NQueenBoard(board_dimension));
            current_attack = current.calculate_attack();
        }
    }
}

void HillClimbingRRWSideWaysNQueens::destroy() {
    //
}