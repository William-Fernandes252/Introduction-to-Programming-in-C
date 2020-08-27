#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

int main(int argc, char ** argv) {
  char ** lines = NULL;
  char * curr = NULL;
  size_t sz;
  size_t i = 0;
  if(argc != 2) {
    printf("Enter one and only one input file.\n");
    exit(EXIT_FAILURE);
  }

  FILE * f = fopen(argv[1], "r");
  if(f == NULL) {
    printf("Failed to open the file.\n");
    exit(EXIT_FAILURE);
  }

  while(getline(&curr, &sz, f) >= 0) {
    lines = realloc(lines,(i + 1) * sizeof(*lines));
    lines[i] = curr;
    curr = NULL;
    i++
  }

  free(curr);
  //Some function that interact with the strings
  sort(lines, i);
  for(size_t j = 0; j < i; j++) {
    free(lines[j]);
  }
  free(lines);

  return(EXIT_SUCCESS);
}
