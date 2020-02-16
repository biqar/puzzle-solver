//
// Created by aislam6 on 2/16/20.
//

#include "../core/heuristic.h"
#include "../core/state.h"

class Manhattan : public Heuristic {
public:
    Manhattan() {
    }

    int guess_distance(State *_current_state, State *_goal_state);
};

int Manhattan::guess_distance(State *_current_state, State *_goal_state) {
    int ret = 0;

    for(int i=0; i<BOARD_DIM_X; i+=1) {
        for(int j=0; j<BOARD_DIM_Y; j+=1) {
            if(_current_state->board[i][j] != BLANK_TILE && _current_state->board[i][j] != _goal_state->board[i][j]) {
                bool found = false;
                for(int ii=0; ii<BOARD_DIM_X; ii+=1) {
                    for(int jj=0; jj<BOARD_DIM_Y; jj+=1) {
                        if(_current_state->board[i][j] == _goal_state->board[ii][jj]) {
                            ret += (utils::_abs(i-ii) + utils::_abs(j-jj));
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