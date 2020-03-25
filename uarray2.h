#ifndef UARRAY2_INCLUDED
#define UARRAY2_INCLUDED

#include <array.h>

typedef struct UArray2_T *UArray2_T;

/*
Constructor: Create two-dimensional array of from given height and width.
Size of elements in the array defined by size
*/
UArray2_T UArray2_new(int height, int width, int size);

//Destructor: Free the two-dimensional array's memory
void UArray_free(UArray2_T *uarray2);

//Applies the funciton to the array row by row
void UArray2_map_row_major(UArray2_T array, void apply(int row, int col, UArray2_T uarray2, int *num, void *closure), void *closure);

//Applies the function to the array col by col
void UArray2_map_col_major(UArray2_T array, void apply(int row, int col, UArray2_T uarray2, int *num, void *colsure), void *closure);

//Retrieve a pointer to the element at coordinate [row][col]
void *UArray2_at(UArray2_T array, int row, int col);

//Returns the width of the array
int UArray2_width(UArray2_T array);

// Returns the height of the array
int UArray2_height(UArray2_T array);

// Returns the size of the elements stored in the array
int UArray2_size(UArray2_T array);

#endif
