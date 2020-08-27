// Return how many letters has in a input file

#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

int main(int argc, char ** argv) {
  if(argc != 2) {
    printf("Usage: ./fgetc inputFile.txt\n");
    exit(EXIT_FAILURE);
  }
  FILE * f = fopen(argv[1], "r");
  if(f == NULL) {
    printf("Failed to open the input file.");
    exit(EXIT_FAILURE);
  }

  int c;
  int letters = 0;
  while((c = fgetc(f)) != EOF) {
    if(isalpha(c)) {
      letters++;
    }
  }
  printf("%s has %d letters in it.\n", argv[1], letters);

  return EXIT_SUCCESS;
}
