//
// Created by aislam6 on 2/16/20.
//

#include "../core/heuristic.h"
#include "../core/state.h"

class Hamming : public Heuristic {
public:
    Hamming() {
    }

    int guess_distance(State *_current_state, State *_goal_state);
};

int Hamming::guess_distance(State *_current_state, State *_goal_state) {
    int ret = 0;

    for(int i=0; i<BOARD_DIM_X; i+=1) {
        for (int j = 0; j < BOARD_DIM_Y; j += 1) {
            if (_current_state->board[i][j] != BLANK_TILE && _current_state->board[i][j] != _goal_state->board[i][j]) {
                ret += 1;
            }
        }
    }

    return ret;
}