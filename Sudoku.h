#ifndef SUDOKU_H
#define SUDOKU_H

#include <vector>
#include <string>
#include <set>
#include <cmath>
#include <iostream>

using namespace std;

class Sudoku{

private:

    int boardSize;
    vector<vector<set<int>>> boardValues;

public:

    explicit Sudoku(int boardSizeIn) : boardSize(boardSizeIn){
        for (int row = 0; row < boardSize; ++row){
            vector<set<int>> columnInit;
            for (int col = 0; col < boardSize; ++col){
                set<int> possibleValuesSet = {};
                for(int value = 1; value <= boardSize; ++value) {
                    possibleValuesSet.insert(value);
                }
                columnInit.emplace_back(possibleValuesSet);
            }
            boardValues.emplace_back(columnInit);
        }
    }

    int getSquare(int row, int col){
        if(boardValues[row][col].size() == 1){
            return *(boardValues[row][col].begin());
        } else {
            return -1;
        }
    }

    bool setSquare(int rowIn, int colIn, int value){

        int row = rowIn;
        int col = colIn;
        set<int> possibleColumns = {};

        clearSquares(row, col, value);

        if (row == boardSize - 1 && col == boardSize - 1){
            int rowAfterPop = 0;
            int colAfterPop = 0;

            while (!isEmpty()) {
                return fillOtherSquares(rowAfterPop, colAfterPop);
            }
            clearOtherSquares();
        }
        clearOtherSquares();
        return true;
    }

    bool fillOtherSquares(int row, int col){
        if (row == boardSize - 1 && col == boardSize){
            return true;
        }

        if (col == boardSize){
            row++;
            col = 0;
        }

        if (boardValues[row][col].size() == 1){
            return fillOtherSquares(row, col + 1);
        }

        while (!isEmpty()) {
            for (int number = 1; number <= boardSize; number++) {
                clearSquares(row, col, number);
                clearOtherSquares();
                if (fillOtherSquares(row, col + 1)) {
                    return true;
                }
            }
        }
        return false;
    }

    bool isEmpty(){
        for(int row = 0; row < boardSize; ++row) {
            for (int col = 0; col < boardSize; ++col) {
                if(boardValues[row][col].size() != 1){
                    return false;
                }
            }
        }
        return true;
    }

    void clearSquares(int row, int col, int value){
        if (isPossibleInSquare(row, col, value)) {
            eraseInRow(row, value);
            eraseInColumn(col, value);
            eraseInBox(row - row % getSizeSmallBox(boardSize) , col - col % getSizeSmallBox(boardSize), value);
            boardValues[row][col] = {value};
        }
    }

    void clearOtherSquares(){
        for (int row = 0; row < boardSize; ++row){
            for (int col = 0; col < boardSize; ++col) {
                if (boardValues[row][col].size() == 1) {
                    int value = *(boardValues[row][col].begin());
                    eraseInRow(row, value);
                    eraseInColumn(col, value);
                    eraseInBox(row - row % getSizeSmallBox(boardSize), col - col % getSizeSmallBox(boardSize), value);
                }
            }
        }
    }

    bool isPossibleInSquare(int row, int col, int value){
        return isPossibleInRow(row, value) && isPossibleInColumn(col, value) && isPossibleInBox(row - row%(getSizeSmallBox(boardSize)), col - col%(getSizeSmallBox(boardSize)), value);
    }

    bool isPossibleInRow(int row, int value){
        for(int col = 0; col < boardSize; ++col){
            if (boardValues[row][col].size() == 1 && *(boardValues[row][col].begin()) == value){
                return false;
            }
        }
        return true;
    }

    void eraseInRow(int row, int value){
        for(int col = 0; col < boardSize; ++col){
            if (boardValues[row][col].size() != 1) {
                boardValues[row][col].erase(value);
            }
        }
    }

    bool isPossibleInColumn(int col, int value){
        for(int row = 0; row < boardSize; ++row){
            if (boardValues[row][col].size() == 1 && *(boardValues[row][col].begin()) == value){
                return false;
            }
        }
        return true;
    }

    void eraseInColumn(int col, int value){
        for(int row = 0; row < boardSize; ++row){
            if (boardValues[row][col].size() != 1){
                boardValues[row][col].erase(value);
            }
        }
    }

    bool isPossibleInBox(int rowStart, int colStart, int value){
        for(int row = 0; row < getSizeSmallBox(boardSize); ++row ){
            for(int col = 0; col < getSizeSmallBox(boardSize); ++col ){
                if (boardValues[row+rowStart][col+colStart].size() == 1 && *(boardValues[row+rowStart][col+colStart].begin()) == value){
                    return false;
                }
            }
        }
        return true;
    }

    void eraseInBox(int rowStart, int colStart, int value){
        for(int row = 0; row < getSizeSmallBox(boardSize); ++row ){
            for(int col = 0; col < getSizeSmallBox(boardSize); ++col ) {
                if (boardValues[row + rowStart][col + colStart].size() != 1) {
                    boardValues[row + rowStart][col + colStart].erase(value);
                }
            }
        }
    }

    static int getSizeSmallBox(int boardSize){
        return (int) sqrt(boardSize);
    }

    void printSudokuGrid(){
        for (int row = 0; row < boardSize; ++row){
            for (int col = 0; col < boardSize; ++col){
                if(col == 3 || col == 6) {
                    cout << " | ";
                }
                if(boardValues[row][col].size() == 1) {
                    cout << *(boardValues[row][col].begin()) << " ";
                } else {
                    cout << "X ";
                }
            }
            if(row == 2 || row == 5){
                cout << endl;
                for(int i = 0; i < boardSize; ++i)
                    cout << "---";
            }
            cout << endl;
        }
    }
};

#endif

