//
// Created by Islam, Abdullah Al Raqibul on 3/22/20.
//

#ifndef PUZZLE_SOLVER_NQUEEN_BOARD_H
#define PUZZLE_SOLVER_NQUEEN_BOARD_H

#include "../../utill/utills.h"

class NQueenBoard {
private:
    int row;
    int column;
public:
    NQueenBoard(int _row, int _column) {
        row = _row;
        column = _column;
    }

    int getRow() {
        return row;
    }

    int getColumn() {
        return column;
    }

    void setRow(int _row) {
        row = _row;
    }

    void setColumn(int _column) {
        column = _column;
    }

    bool isConflict(NQueenBoard board) {
        //check if two queens line on the same row or column
        if(row == board.getRow() || column == board.getColumn()) return true;
        //check if two queens line on the same diagonal
        if(utils::_abs(row-board.getRow()) == utils::_abs(column-board.getColumn())) return true;

        return false;
    }

    void move() {
        row += 1;
    }
};


#endif //PUZZLE_SOLVER_NQUEEN_BOARD_H
