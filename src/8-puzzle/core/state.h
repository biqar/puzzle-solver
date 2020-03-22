//
// Created by Islam, Abdullah Al Raqibul on 1/30/20.
//

#ifndef STATE_H
#define STATE_H

#include "../../utill/utills.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <algorithm>
#include <sstream>

#define BLANK_TILE 0
#define BOARD_DIM_X 3
#define BOARD_DIM_Y 3

#define STATE_SEPARATOR ','
#define CHAR_SPACE ' '

typedef enum Move {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    MOVE_MAX
} Move;

typedef struct State {
    Move move;      //the last move that brings this board state
    int board[BOARD_DIM_X][BOARD_DIM_Y];
} State;

/**
 * this method will generate a @return{new_state} from the @param{current_state} with the help of @param{move}
 * */
inline State *move_to_new_state(State *current_state, Move move) {
    State *new_state = (State *) malloc(sizeof(State));
    int blk_row = -1, blk_col = -1;

    for(int i=0; i<BOARD_DIM_X; i+=1) {
        for(int j=0; j<BOARD_DIM_Y; j+=1) {
            new_state->board[i][j] = current_state->board[i][j];
            if(current_state->board[i][j] == BLANK_TILE) {
                blk_row = i;
                blk_col = j;
            }
        }
    }

    if (move == UP && blk_row - 1 >= 0) {
        int tmp = new_state->board[blk_row - 1][blk_col];
        new_state->board[blk_row - 1][blk_col] = BLANK_TILE;
        new_state->board[blk_row][blk_col] = tmp;
        new_state->move = UP;
        return new_state;
    }
    else if (move == DOWN && blk_row + 1 < BOARD_DIM_X) {
        int tmp = new_state->board[blk_row + 1][blk_col];
        new_state->board[blk_row + 1][blk_col] = BLANK_TILE;
        new_state->board[blk_row][blk_col] = tmp;
        new_state->move = DOWN;
        return new_state;
    }
    else if (move == LEFT && blk_col - 1 >= 0) {
        int tmp = new_state->board[blk_row][blk_col - 1];
        new_state->board[blk_row][blk_col - 1] = BLANK_TILE;
        new_state->board[blk_row][blk_col] = tmp;
        new_state->move = LEFT;
        return new_state;
    }
    else if (move == RIGHT && blk_col + 1 < BOARD_DIM_Y) {
        int tmp = new_state->board[blk_row][blk_col + 1];
        new_state->board[blk_row][blk_col + 1] = BLANK_TILE;
        new_state->board[blk_row][blk_col] = tmp;
        new_state->move = RIGHT;
        return new_state;
    }

    free(new_state);
    return new_state = NULL;
}

inline bool equal_state(State *current_state, State *compare_state) {
    for(int i=0; i<BOARD_DIM_X; i+=1) {
        for (int j = 0; j < BOARD_DIM_Y; j += 1) {
            if (current_state->board[i][j] != compare_state->board[i][j]) {
                return false;
            }
        }
    }

    return true;
}

inline void print_board(State *state) {
    for(int i=0; i<BOARD_DIM_X; i+=1) {
        for(int j=0; j<BOARD_DIM_Y; j+=1) {
            printf(" %d", state->board[i][j]);
        }
        printf("\n");
    }
    //printf("\n");
}

inline State *construct_goal_state() {
    State *goal_state = (State *) malloc(sizeof(State));

    goal_state->board[0][0] = 1;
    goal_state->board[0][1] = 2;
    goal_state->board[0][2] = 3;

    goal_state->board[1][0] = 4;
    goal_state->board[1][1] = 5;
    goal_state->board[1][2] = 6;

    goal_state->board[2][0] = 7;
    goal_state->board[2][1] = 8;
    goal_state->board[2][2] = 0;

    goal_state->move = MOVE_MAX;

    return goal_state;
}

inline State *construct_initial_state() {
    State *initial_state = (State *) malloc(sizeof(State));

    initial_state->board[0][0] = 1;
    initial_state->board[0][1] = 2;
    initial_state->board[0][2] = 0;

    initial_state->board[1][0] = 4;
    initial_state->board[1][1] = 5;
    initial_state->board[1][2] = 3;

    initial_state->board[2][0] = 7;
    initial_state->board[2][1] = 8;
    initial_state->board[2][2] = 6;

    initial_state->move = MOVE_MAX;

    return initial_state;
}

inline State *construct_state(std::string state_str) {
    std::replace(state_str.begin(), state_str.end(), STATE_SEPARATOR, CHAR_SPACE);
    std::stringstream ss(state_str);
    State *state = (State *) malloc(sizeof(State));

    ss >> state->board[0][0];
    ss >> state->board[0][1];
    ss >> state->board[0][2];

    ss >> state->board[1][0];
    ss >> state->board[1][1];
    ss >> state->board[1][2];

    ss >> state->board[2][0];
    ss >> state->board[2][1];
    ss >> state->board[2][2];

    state->move = MOVE_MAX;

    return state;
}

inline long long int construct_board_key(State *_state) {
    long long int ret = 0;

    for(int i=0; i<BOARD_DIM_X; i+=1) {
        for (int j = 0; j < BOARD_DIM_Y; j += 1) {
            ret *= 10;
            ret += _state->board[i][j];
        }
    }

    return ret;
}

#endif //STATE_H
