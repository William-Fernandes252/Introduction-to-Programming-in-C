#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "rotate.c"
#define COLUMNS 10
#define ROWS 10

void readInputMatrix(FILE * stream, char * matrix) {
  char row[COLUMNS + 1];
  char * newLineLoc;
  int numRows = 0;

  while(fgets(row, COLUMNS + 2, stream) != NULL) {
    numRows++;
    if(numRows > ROWS) {
      fprintf(stderr, "Too many rows!\n");
      exit(EXIT_FAILURE);
    }

    newLineLoc = strchr(row, '\n');
    if(newLineLoc != (row + ROWS)) {
      fprintf(stderr, "Row too long or too short!\n");
      exit(EXIT_FAILURE);
    }

    for(size_t i = 0; i < COLUMNS; i++) {
      matrix[(numRows - 1) * ROWS + 1] = row[i];
    }
  }

  if(numRows < ROWS) {
    fprintf(stderr, "Too few rows!\n");
    exit(EXIT_FAILURE);
  }
}

int main(int argc, char ** argv) {
  if(argc != 2) {
    fprintf(stderr, "Usage: ./rotation inputFile10by10matrix.txt\n");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1], "r");
  if(f == NULL) {
    fprintf(stderr, "Failed to open the input file.\n");
    return EXIT_FAILURE;
  }

  char inputMatrix[10][10];
  char * matrixLoc = &inputMatrix[0][0];

  readInputMatrix(f, matrixLoc);

  rotate(inputMatrix);

  for(int i = 0; i < ROWS; i++) {
    for(int j = 0; j < COLUMNS; j++) {
      printf("%c", inputMatrix[i][j]);
    }
    printf("\n");
  }
  return EXIT_SUCCESS;
}
