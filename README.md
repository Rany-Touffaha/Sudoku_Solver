# Sudoku_Solver

This program is a sudoku solver for easy puzzles. It is implemented as vector of a vector of a set. 
When initialised, the board size needs to be provided and has to be a square number (9, 16, 25...). 
The board is then of size NxN where each square is a set<int> containing {1,2,3,4,5,6,7,8,9}. 
Whenever a solution is found in one of the squares, the board updates itself by removing the value of that square in all the other sets in the row, column and box.
The board keeps on updating until each square only has one value in its set (size of the set becomes 1). 

The board is then compared to the solution given and if it is the same, it prints out the solution of the board and a message saying that the puzzle has been solved.
Otherwise, it prints out an error message if there has been an issue of inputting the values intially or if the solution found is different from the solution provided.
