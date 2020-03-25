//Declare behavior of URarray2_T

#include <stdlib.h>
#include <stdio.h>
#include "uarray2.h"
#include "array.h"

/*
 *Stuct modeling a 2D array. Contains the attributes height width and size of elements stored.
 *Also contains Hanson Uarray that we will use to represent our 2D array.
 */

struct UArray2_T{
	int height;
	int width;
	int size;
	Array_T array;
};

/*
 *Create new unboxed 2D array width x height
 *Size is the number of bytes needed for each array element
 *Returns 1D representation of a 2D matrix of type UArray2_T
 */
UArray2_T UArray2_new(int width, int height, int size){
	//Check for valid dimensions
	if(width == 0 && height == 0){
		exit(1);
	}


	//Check for valid data size
	if(size == 0){
		exit(1);
	}


	//Represent 2D unboxed array as 1D array of length width * height
	int len = width * height;


	//Check this type**
	UArray2_T arrayPtr = malloc(sizeof(*arrayPtr));

	//Allocate 1D hanson array to represent our 2D matrix
	Array_T array = Array_new(len, size);

	arrayPtr->array = array;
	arrayPtr->height = height;
	arrayPtr->width = width;
	arrayPtr->size = size;

	return arrayPtr;

}

/* Returns a pointer to the requested location [row][col]
 * Takes in a Uarray2T array along with row and col indecies
 */
void *UArray2_at(UArray2_T arrayPtr, int row, int col){
	//Check the given row is in bounds
	if(row < 0 && arrayPtr->height < row){
		exit(1);
	}

	//Check the given column is in bounds
	if(col < 0 && arrayPtr->width < col){
		exit(1);
	}

	//Using our invariant i = (y * width) + x we can get our 1D array index
	int location = (row * arrayPtr->width) + col;

	/* Create a pointer the to desired index of our 1D representation
	 * We can use Hanson's Uarray_T Uarray_ at function with our derived 1D index
	 *to point to the correct spot in memory
	 */
	void *index = Array_get(arrayPtr->array, location);

	return index;

}

//Returns the size of the elements stored in a UArray2_T array
int UArray2_size(UArray2_T arrayPtr){
	return arrayPtr->size;
}

//Returns the width of a UArray2_T array
int UArray2_width(UArray2_T arrayPtr){
	return arrayPtr->width;
}

//Returns the height of a UArray2_T array
int UArray_height(UArray2_T arrayPtr){
	return arrayPtr->height;
}

/*Calls apply function on all elements in UArray2_T array row by row
 *Take a UArray2_T array, a function to be applied, column, and row
 *Returns when operation is complete
 */
void UArray_map_row_major(UArray2_T array, void apply(int row, int col, UArray2_T array, int *num, void *closure), void *closure){
	for(int i = 0; i < array->height; i++){
		for(int j = 0; j < array->width; j++){
			apply(j, i, array, UArray2_at(array, j, i), closure);
		}
	}
}

/*Calls apply function on all elements in UArray2_T array column by column
 * Takes a UArray2_T array, a function to be applied, column, and row
 * Returns when operation is complete
 */
void UArray_map_col_major(UArray2_T array, void apply(int row, int col, UArray2_T array, int *num, void *closure), void *closure){
	for(int i = 0; i < array->width; i++){
		for(int j = 0; j < array->height; j++){
			apply(i, j, array, UArray2_at(array, i, j), closure);
		}
	}
}

/*Frees the allocated memory for our 1D representation and the 2D struct
 *Takes pointer to UArray2_T
 *Returns when operation is complete
 */
void Uarray2_free(UArray2_T *arrayPtr){
	Array_free(&((*arrayPtr)->array));
	free(*arrayPtr);
	return;
}
