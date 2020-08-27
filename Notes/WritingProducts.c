// Return the product of the numbers entered as arguments by the user writing it in a output file

#include<stdio.h>
#include<stdlib.h>
#include<ctype>

int main(int argc, char **  argv) {
  if(argc != 4) {
    printf("Usage: ./WritingProducts.c F1 F2 outputFile.txt\n");
    exit(EXIT_FAILURE);
  }
  int start = atoi(argv[1]);
  int end = atoi(argv[2]);
  FILE * f = fopen(argv[3], "w");
  if(f == NULL) {
    printf("Failed to open the file.\n");
    exit(EXIT_FAILURE);
  }

  for(size_t i = start; i <= end; i++) {
    fprintf(f, "%d\n", i*i);
  }

  int close = fclose(f);
  if(close != 0) {
    printf("Failed to write to the disk! Data was lost.\n")
  }
}
