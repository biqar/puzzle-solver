//
// Created by aislam6 on 2/16/20.
//

#include "../../core/heuristic.h"
#include "../core/state.h"

class Euclidean : public Heuristic {
public:
    Euclidean() {
    }

    int guess_distance(void *_parameter);
};

//todo: need to confirm if: without square-root, euclidean distance is a Admissible Heuristics
int Euclidean::guess_distance(void *_parameter) {
    State *_current_state = ((EightPuzzleHeuristicParam *) _parameter)->current_state;
    State *_goal_state = ((EightPuzzleHeuristicParam *) _parameter)->goal_state;
    int ret = 0;

    for(int i=0; i<BOARD_DIM_X; i+=1) {
        for(int j=0; j<BOARD_DIM_Y; j+=1) {
            if(_current_state->board[i][j] != BLANK_TILE && _current_state->board[i][j] != _goal_state->board[i][j]) {
                bool found = false;
                for(int ii=0; ii<BOARD_DIM_X; ii+=1) {
                    for(int jj=0; jj<BOARD_DIM_Y; jj+=1) {
                        if(_current_state->board[i][j] == _goal_state->board[ii][jj]) {
                            ret += (((i-ii)*(i-ii)) + ((j-jj)*(j-jj)));
                            found = true;
                            break;
                        }
                    }
                    if(found) break;
                }
            }
        }
    }

    return ret;
}