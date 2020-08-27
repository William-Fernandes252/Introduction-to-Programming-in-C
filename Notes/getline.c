#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

int main(int argc, char ** argv) {
  if(argc != 2) {
    printf("Enter one and only one input file.\n");
    exit(EXIT_FAILURE);
  }
  size_t sz = 0;
  ssize_t len = 0;
  char * line = NULL;

  FILE * f = fopen(argv[1], "r");
  if(f == NULL) {
    printf("Failed to open the input file\n");
    exit(EXIT_FAILURE);
  }

  while((len = getline(&line, &sz, f)) >= 0) {
    printf("%s", line);
  }
  free(line);
  int c = fclose(f);
  if(c != 0) {
    printf("Failed to close the input file. Data is lost.\n");
    exit(EXIT_FAILURE);
  }

  return EXIT_SUCCESS;
}
