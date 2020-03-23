//
// Created by Islam, Abdullah Al Raqibul on 3/22/20.
//

#ifndef PUZZLE_SOLVER_NQUEEN_BOARD_H
#define PUZZLE_SOLVER_NQUEEN_BOARD_H

#include "queen.h"
#include <vector>

class NQueenBoard {
private:
    int dim;
    std::vector<NQueen> queens;
public:
    NQueenBoard() {}

    NQueenBoard(int _dim) {
        dim = _dim;
        // for each column, place a queen in a random row
        for(int i=0; i<_dim; i+=1) {
            NQueen nQueen(rand() % _dim, i);
            queens.push_back(nQueen);
        }
    }

    int calculate_attack() {
        int attack = 0;
        for(int i=0; i<dim; i+=1) {
            for(int j=i+1; j<dim; j+=1) {
                if(queens[i].isConflict(queens[j])) {
                    attack += 1;
                }
            }
        }
        return attack;
    }

    NQueenBoard best_successor() {
        int current_row, current_column;
        int min_attack = dim * dim, current_attack;
        NQueenBoard best;
        NQueenBoard tmp = (*this);

        for(int i=0; i<dim; i+=1) {
            current_row = tmp.queens[i].getRow();
            current_column = tmp.queens[i].getColumn();

            while(tmp.queens[i].move_up()) {
                current_attack = tmp.calculate_attack();
                if(current_attack < min_attack) {
                    min_attack = current_attack;
                    best = tmp;
                }
            }

            tmp.queens[i].setRow(current_row);
            tmp.queens[i].setColumn(current_column);

            while(tmp.queens[i].move_down(dim)) {
                current_attack = tmp.calculate_attack();
                if(current_attack < min_attack) {
                    min_attack = current_attack;
                    best = tmp;
                }
            }

            tmp.queens[i].setRow(current_row);
            tmp.queens[i].setColumn(current_column);
        }
        return best;
    }

    NQueenBoard best_successor_v1() {
        int current_row, current_column;
        int min_attack = dim * dim, current_attack;
        std::vector<NQueenBoard> bests;
        NQueenBoard tmp = (*this);

        for(int i=0; i<dim; i+=1) {
            current_row = tmp.queens[i].getRow();
            current_column = tmp.queens[i].getColumn();

            while(tmp.queens[i].move_up()) {
                current_attack = tmp.calculate_attack();
                if(current_attack < min_attack) {
                    min_attack = current_attack;
                    bests.clear();
                    bests.push_back(tmp);
                }
                else if (current_attack == min_attack) {
                    bests.push_back(tmp);
                }
            }

            tmp.queens[i].setRow(current_row);
            tmp.queens[i].setColumn(current_column);

            while(tmp.queens[i].move_down(dim)) {
                current_attack = tmp.calculate_attack();
                if(current_attack < min_attack) {
                    min_attack = current_attack;
                    bests.clear();
                    bests.push_back(tmp);
                }
                else if (current_attack == min_attack) {
                    bests.push_back(tmp);
                }
            }

            tmp.queens[i].setRow(current_row);
            tmp.queens[i].setColumn(current_column);
        }
        return bests[rand() % bests.size()];
    }

    int getDim() {
        return dim;
    }

    void setDim(int _dim) {
        dim = _dim;
    }

    std::vector<NQueen> getBQueens() {
        return queens;
    }

    void setQueens(std::vector<NQueen> _queens) {
        queens = _queens;
    }
};

#endif //PUZZLE_SOLVER_NQUEEN_BOARD_H
