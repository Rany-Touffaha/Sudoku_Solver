#include "Sudoku.h"

bool fillBoard(Sudoku * board, const vector<vector<set<int>>> & fillWith) {
    for (int row = 0; row < fillWith.size(); ++row) {
        for (int col = 0; col < fillWith.size(); ++col) {
            if (fillWith[row][col].size() == 1) {
                const int setTo = *(fillWith[row][col].begin());
                if (!board->setSquare(row, col, setTo)) {
                    cout << "Error: setSquare returned false after setting square[" << row << "][" << col << "] to " << setTo << endl;
                    return false;
                }
            }
        }
    }
    return true;
}

bool checkAnswer(Sudoku * board, const vector<vector<set<int>>> & answer) {
    for (int row = 0; row < answer.size(); ++row) {
        for (int col = 0; col < answer.size(); ++col) {
            const int setTo = *(answer[row][col].begin());
            if (board->getSquare(row,col) != setTo) {
                cout << "Error: wrong answer in square[" << row << "][" << col << "]: should be " << setTo << " but is " << board->getSquare(row,col) << endl;
                return false;
            }
        }
    }
    return true;
}

int main() {

    vector<vector<set<int>>> boardOneInput {
            {{2}, {3}, {},  {9}, {1}, {5}, {},  {},  {}},
            {{},  {},  {},  {2}, {},  {},  {5}, {4}, {}},
            {{6}, {},  {7}, {},  {},  {},  {},  {},  {}},
            {{},  {},  {1}, {},  {},  {},  {},  {},  {9}},
            {{8}, {9}, {},  {5}, {},  {3}, {},  {1}, {7}},
            {{5}, {},  {},  {},  {},  {},  {6}, {},  {}},
            {{},  {},  {},  {},  {},  {},  {9}, {},  {5}},
            {{},  {1}, {6}, {},  {},  {7}, {},  {},  {}},
            {{},  {},  {},  {3}, {2}, {9}, {},  {},  {1}},
    };

    vector<vector<set<int>>> boardOneSolution {
            {{2}, {3}, {4}, {9}, {1}, {5}, {7}, {8}, {6}},
            {{1}, {8}, {9}, {2}, {7}, {6}, {5}, {4}, {3}},
            {{6}, {5}, {7}, {4}, {3}, {8}, {1}, {9}, {2}},
            {{4}, {6}, {1}, {7}, {8}, {2}, {3}, {5}, {9}},
            {{8}, {9}, {2}, {5}, {6}, {3}, {4}, {1}, {7}},
            {{5}, {7}, {3}, {1}, {9}, {4}, {6}, {2}, {8}},
            {{3}, {2}, {8}, {6}, {4}, {1}, {9}, {7}, {5}},
            {{9}, {1}, {6}, {8}, {5}, {7}, {2}, {3}, {4}},
            {{7}, {4}, {5}, {3}, {2}, {9}, {8}, {6}, {1}},
    };

    vector<vector<set<int>>> boardTwoInput {
            {{2}, {},  {},  {8}, {},  {4}, {},  {},  {6}},
            {{},  {},  {6}, {},  {},  {},  {5}, {},  {}},
            {{},  {7}, {4}, {},  {},  {},  {9}, {2}, {}},
            {{3}, {},  {},  {},  {4}, {},  {},  {},  {7}},
            {{},  {},  {},  {3}, {},  {5}, {},  {},  {}},
            {{4}, {},  {},  {},  {6}, {},  {},  {},  {9}},
            {{},  {1}, {9}, {},  {},  {},  {7}, {4}, {}},
            {{},  {},  {8}, {},  {},  {},  {2}, {},  {}},
            {{5}, {},  {},  {6}, {},  {8}, {},  {},  {1}},
    };

    vector<vector<set<int>>> boardTwoSolution {
            {{2}, {5}, {3}, {8}, {9}, {4}, {1}, {7}, {6}},
            {{1}, {9}, {6}, {2}, {3}, {7}, {5}, {8}, {4}},
            {{8}, {7}, {4}, {1}, {5}, {6}, {9}, {2}, {3}},
            {{3}, {8}, {1}, {9}, {4}, {2}, {6}, {5}, {7}},
            {{9}, {6}, {7}, {3}, {8}, {5}, {4}, {1}, {2}},
            {{4}, {2}, {5}, {7}, {6}, {1}, {8}, {3}, {9}},
            {{6}, {1}, {9}, {5}, {2}, {3}, {7}, {4}, {8}},
            {{7}, {3}, {8}, {4}, {1}, {9}, {2}, {6}, {5}},
            {{5}, {4}, {2}, {6}, {7}, {8}, {3}, {9}, {1}},
    };


    unique_ptr<Sudoku> board1(new Sudoku(9));
    unique_ptr<Sudoku> board2(new Sudoku(9));


    if (!fillBoard(board1.get(), boardOneInput)) {
        cout << "The wrong values were added to the first board" << endl;
        board1->printSudokuGrid();
        return 1;
    }

    if (!checkAnswer(board1.get(), boardOneSolution)) {
        cout << "The first board has the wrong values in it" << endl;
        board1->printSudokuGrid();
        return 1;
    }

    if (!fillBoard(board2.get(), boardTwoInput)) {
        cout << "The wrong values were added to the first board" << endl;
        board2->printSudokuGrid();
        return 1;
    }

    if (!checkAnswer(board2.get(), boardTwoSolution)) {
        cout << "The first board has the wrong values in it" << endl;
        board2->printSudokuGrid();
        return 1;
    }

    board1->printSudokuGrid();
    cout << endl;
    board2->printSudokuGrid();

    cout << "Both boards have been solved. Every square had the right answer" << endl;
    return 0;
}
