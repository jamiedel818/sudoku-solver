#include <stdio.h>
#include <stdlib.h>
#include "pnmrdr.h"
#include "uarray2.h"
#include "assert.h"

//Declare global variables to compare validity of sudoku puzzle
const int multiCheck = 362880;
const int addCheck = 45;

//Checks the validity of all the 3x3 sub matricies that the sudoku puzzle contains
//If there is a repeated value in the sub matrice the puzzle is not valid
void checkBox(UArray2_T array){
  //this array is to keep track of the index of the top left index of each box
  int boxStart[9] = {0, 3, 6, 27, 30, 33, 54, 57, 60};
  int track = 0;

  //initialize tracking variables
  int multi = 1;
  int add = 0;

  int i = 0;
  int j = 0;
  int k = 0;

  int row;
  int col;

  int* num;

  //iterates 9 times for 9 boxes
  while(i < 9){
    //each iteration set location for next box
    track = boxStart[i];

    //iteartes 3 times for 3 rows in each box
    while(j < 3){
      //iterates 3 times to get each row's values in the box
      while(k < 3){
        //perform arithmetic to access the correct index in the array
        row = track / 9;
        col = track % 9;

        //get the value at the index
        num = UArray2_at(array, row, col);

        //increment by current value for running totals
        multi *= (*num);
        add += (*num);

        track += 1;
        k += 1;
      }

      //increment track variable by 6 in order to be in the correct position.
      track += 6;
      k = 0;
      j += 1;
    }


    //perform check on multi and add to determine if box is valid
    if(multi != multiCheck || add != addCheck){
      exit(1);
    }

    multi = 1;
    add = 0;

    j = 0;
    i += 1;
  }
}

//Checks the validity of a sudoku puzzle by scanning each value row by row
//If a duplicate is found the puzzle is not valid
void checkRow(UArray2_T array){
  int multi = 1;
  int add = 0;

  int *num;

  //this for loop goes row by row checking the validity of each row
  //if either multi or add is not equal to the correct values the row is invalid
  for(int i = 0; i < 9; i++){
    for(int j = 0; j < 9; j++){
      num = UArray2_at(array, i, j);
      multi *= (*num);
      add += (*num);
    }
    if(multi != multiCheck || add != addCheck){
      exit(1);
    }
    multi = 1;
    add = 0;
  }
}

//Checks the validity of a sudoku puzzle by scanning each value column by column
//If a duplicate is found the puzzle is not valid
void checkCol(UArray2_T array){
  int multi = 1;
  int add = 0;

  int i = 0;
  int j = 0;

  int *num;

  //this while loop goes column by column checking the validity of each column
  //if either multi or add is not equal to the correct values the column is invalid
  while(i < 9){
    while(j < 9){
      num = UArray2_at(array, j, i);
      multi *= (*num);
      add += (*num);
      j += 1;
    }
    if(multi != multiCheck || add != addCheck){
      exit(1);
    }
    multi = 1;
    add = 0;
    j = 0;
    i += 1;
  }
}

int main(int argc, const char* argv[]){
  //perform file i/o
  assert(argc <= 2);

  FILE *image;
  UArray2_T puzzle = UArray2_new(9,9,sizeof(int));

  if(argc == 1){
    image = stdin;
    assert(image != NULL);
  }

  else{
    image = fopen(argv[1], "rb");
    assert(image != NULL);
  }


  void *imageReader = Pnmrdr_new(image);
  Pnmrdr_mapdata imageData = Pnmrdr_data(imageReader);

  int denominator = imageData.denominator;
  int height = imageData.height;
  int width = imageData.width;

  //declare the correct assertions for project specifications
  assert(imageData.type == Pnmrdr_gray);
  assert(denominator == 9);
  assert(height == 9);
  assert(width == 9);

  int *num;

  //fill array with values from file
  for(int i = 0; i < height; i++){
    for(int j = 0; j < width; j++){
	    int pixel = Pnmrdr_get(imageReader);
      assert(pixel < 10 && pixel > 0);
      num = UArray2_at(puzzle, i,j);
      *num = pixel;
    }
  }

  //call functions to check validity of sudoku
  checkRow(puzzle);
  checkCol(puzzle);
  checkBox(puzzle);

  fclose(image);

  Pnmrdr_free((Pnmrdr_T *)&imageReader);

  exit(0);

}
