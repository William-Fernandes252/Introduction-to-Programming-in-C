#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"
#include "counts.h"
#include "outname.h"

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  //WRITE ME
  FILE * keyFILE = fopen(filename, "r");
  if(keyFILE == NULL) {
    fprintf(stderr, "Problem opening the key file\n");
    exit(EXIT_FAILURE);
  }

  counts_t * curCounts = createCounts();

  size_t lineSize = 0;
  char * curKey = NULL;
  size_t curKeyLen = 0;
  char * curValue = NULL;
  while(getline(&curKey, &lineSize, keyFILE) > 0) {
    curKeyLen = strlen(curKey);
    curKey[curKeyLen - 1] = '\0';
    curValue = lookupValue(kvPairs, curKey);
    addCount(curCounts, curValue);
  }

  free(curKey);

  if(fclose(keyFILE) != 0) {
    fprintf(stderr, "Problem occured while closing the file. Data lost.\n");
    exit(EXIT_FAILURE);
  }
  
  return curCounts;
}

int main(int argc, char ** argv) {
  if(argc < 2) {
    fprintf(stderr, "Enter the name of the program , them the input files.\n");
    exit(EXIT_FAILURE);
  }

  kvarray_t * kv = readKVs(argv[1]);

  for(size_t i = 2; i < argc; i++) {
    counts_t * c = countFile(argv[i], kv);
    char * outName = computeOutputFileName(argv[i]);

    FILE * f = fopen(outName, "w+");
    if(f == NULL) {
      fprintf(stderr, "Failed to open the input files.\n");
      exit(EXIT_FAILURE);
    }

    printCounts(c, f);

    if(fclose(f) != 0) {
      fprintf(stderr, "Failed to close the input files. Data was lost.\n");
      exit(EXIT_FAILURE);
    }

    free(outName);
    freeCounts(c);
  }

  freeKVs(kv);
  
  return EXIT_SUCCESS;
}
