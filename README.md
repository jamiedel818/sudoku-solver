# sudoku-solver

Public version of CSC411 Sudoku Solver.
Credit to ChristopherPolanco as well

uarray2.c/uarray2.h
Defines 2d arrary interface UArray2. Each 2d array has the properties of width, height, and size. Implemented row-major, column-major, and block-major function mapping.

sudoku.c
Represents sudoku puzzle as a two dimensional array. 
Checks the puzzle's validity by row, column, and block mapping.
Returns 0 for a valid puzzle.

