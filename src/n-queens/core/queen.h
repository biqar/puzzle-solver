//
// Created by Islam, Abdullah Al Raqibul on 3/22/20.
//

#ifndef PUZZLE_SOLVER_NQUEEN_H
#define PUZZLE_SOLVER_NQUEEN_H

#include "../../utill/utills.h"

class NQueen {
private:
    int row;
    int column;
public:
    NQueen(int _row, int _column) {
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

    bool isConflict(NQueen another_queen) {
        //check if two queens line on the same row or column
        if(row == another_queen.getRow() || column == another_queen.getColumn()) return true;
        //check if two queens line on the same diagonal
        if(utils::_abs(row-another_queen.getRow()) == utils::_abs(column-another_queen.getColumn())) return true;

        return false;
    }

    bool is_valid(int dim) {
        if(row >= 0 && row < dim && column >= 0 && column < dim) return true;
        return false;
    }

    bool move_up() {
        if(row > 0) {
            row -= 1;
            return true;
        }
        return false;
    }

    bool move_down(int dim) {
        if(row < dim-1) {
            row += 1;
            return true;
        }
        return false;
    }
};

#endif //PUZZLE_SOLVER_NQUEEN_H
