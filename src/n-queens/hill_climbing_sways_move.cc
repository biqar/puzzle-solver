//
// Created by Islam, Abdullah Al Raqibul on 3/22/20.
//

#include "core/queen.h"

class HillClimbingWSideWaysNQueens : public Solver {
public:
    HillClimbingWSideWaysNQueens(void *_parameter) {
        HillClimbingWSideWaysNQueens::init(_parameter);
    }

    int init(void *_parameter);

    int run();

    void destroy();

private:
    /* Private Data */
    int board_dimension;
    int mx_sideways_move;
    bool print_path;
    vector<NQueenBoard> path;

    NQueenBoard *initial_state;
};

int HillClimbingWSideWaysNQueens::init(void *_parameter) {
    board_dimension = ((NQueenInitParam *)_parameter)->board_dimension;
    mx_sideways_move = ((NQueenInitParam *)_parameter)->mx_sideways_move;
    print_path = ((NQueenInitParam *)_parameter)->print_path;

    srand (time(NULL)); //initialize random seed
    initial_state = new NQueenBoard(board_dimension);
    return 1;
}

int HillClimbingWSideWaysNQueens::run() {
    NQueenBoard next = NULL;
    NQueenBoard current = *initial_state;
    int iteration = 0;
    int sideways_move = 0;
    int current_attack = current.calculate_attack(), next_attack;

    if(print_path) path.push_back(current);

    while(true) {
        iteration += 1;
        next = current.best_successor();
        next_attack = next.calculate_attack();

        if(print_path) path.push_back(next);

        //printf("current attack: %d, next attack: %d\n", current_attack, next_attack);
        if(next_attack == 0) {
            printf("[success] %d\n", iteration);
            if(print_path) {
                int path_size = path.size();
                for(int i=0; i<path_size; i+=1) {
                    path[i].print_board();
                }
            }
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
                return 0;
            }
        }
        else {
            printf("[failure] %d\n", iteration);
            return 0;
        }
    }
}

void HillClimbingWSideWaysNQueens::destroy() {
    free(initial_state);
}