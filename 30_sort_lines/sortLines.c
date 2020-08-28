#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//This function is used to figure out the ordering
//of the strings in qsort.  You do not need
//to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort and print data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}

void getAndSortData(FILE * inputFile) {
  char ** lines = NULL;
  char * curr = NULL;
  size_t lineSize = 0;
  size_t nLines = 0; 
  while(getline(&curr, &lineSize, inputFile) >= 0) {
    nLines++;
    lines = realloc(lines, nLines * sizeof(*lines));
    if(lines == NULL) {
      fprintf(stderr, "Something wrong with the data.\n");
    }
    lines[nLines - 1] = curr;
    curr = NULL;
  }
  
  free(curr);

  if(nLines < 2) {
    fprintf(stderr, "Not enough lines");
    exit(EXIT_FAILURE);
  }
  
  sortData(lines, nLines);

  for(size_t j = 0; j < nLines; j++) {
    printf("%s", lines[j]);
    free(lines[j]);
  }
  
  free(lines);
}

int main(int argc, char ** argv) {
  if(argc == 1) {
    getAndSortData(stdin);
  }
  else if(argc > 1) {
    for(size_t i = 1; i < argc; ++i) {
      FILE * f = fopen(argv[i], "r");
      if(f == NULL) {
	fprintf(stderr, "Failed to open the file.\n");
	return EXIT_FAILURE;
      }

      getAndSortData(f);
      if(fclose(f) != 0) {
	fprintf(stderr, "Failed to close one of the input files. Data was lost.\n");
	return EXIT_FAILURE;
      }
    }
  }
  else {
    fprintf(stderr, "Some problem occured. Closing the session.\n");
    return EXIT_FAILURE;
  }
  
  return EXIT_SUCCESS;
}
