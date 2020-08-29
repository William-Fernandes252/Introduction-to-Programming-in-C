#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "counts.h"
counts_t * createCounts(void) {
  //WRITE ME
  counts_t * cntsStruct = malloc(sizeof(counts_t));
  cntsStruct->oneCntArray = NULL;
  cntsStruct->nStr = 0;
  cntsStruct->nUnk = 0;
  return cntsStruct;
}
void addCount(counts_t * c, const char * name) {
  //WRITE ME
  if(name == NULL) {
    c->nUnk++;
  }
  else {
    size_t i = 0;
    int newStr = 1;
    while(i < c->nStr) {
      if(strcmp(name, c->oneCntArray[i]->str) == 0) {
	c->oneCntArray[i]->strCnt++;
	i++;
	newStr = 0;
      }
      else {
	i++;
      }
    }
    if(newStr == 1) {
      c->nStr++;
      c->oneCntArray = realloc(c->oneCntArray, (c->nStr) * sizeof(one_count_t*));
      c->oneCntArray[c->nStr - 1] = malloc(sizeof(one_count_t));
      c->oneCntArray[c->nStr - 1]->str = strdup(name);
      c->oneCntArray[c->nStr - 1]->strCnt = 1;
    }
  }
}

void printCounts(counts_t * c, FILE * outFile) {
  //WRITE ME
  for(size_t i = 0; i < c->nStr; i++) {
    fprintf(outFile, "%s: %zu\n", c->oneCntArray[i]->str, c->oneCntArray[i]->strCnt);
  }
  if(c->nUnk != 0) {
    fprintf(outFile, "<unknown> : %zu\n", c->nUnk);
  }
}

void freeCounts(counts_t * c) {
  //WRITE ME
  for(size_t i = 0; i < c->nStr; i++) {
    free(c->oneCntArray[i]->str);
    free(c->oneCntArray[i]);
  }
  free(c->oneCntArray);
  free(c);
}
