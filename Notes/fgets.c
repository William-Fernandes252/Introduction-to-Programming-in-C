// Sum number up to 5 digits listened in a file

#include<stdio.h>
#include<stdlib.h>
#include<ctype>
#define LINE_SIZE 5

int main(int argc, char ** argv) {
  if(argc != 2) {
    printf("Usage: ./fgets inputFile.txt");
    exit(EXIT_FAILURE);
  }
  FILE * f = fopen(argv[1], "r");
  if(f == NULL) {
    printf("Failed to open the file.");
    exit(EXIT_FAILURE);
  }
  long total = 0;
  char line[LINE_SIZE];
  while(fgets(line, LINE_SIZE, f) != NULL) {
    if(strchr(line, '\n') == NULL) {
      printf("Line is too long!");
      return EXIT_FAILURE;
    }
    total += atoi(line);
    /* the function "atoi" basicaly converts text numbers to values for variables*/
  }
  printf("The sum is %d.\n", total);

  return EXIT_SUCCESS;
}
