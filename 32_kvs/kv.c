#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"

char *  getKey(char * line) {
  size_t keyLen = (strchr(line, '=') - line);
  char keyStr[keyLen + 1];
  memset(keyStr, '\0', keyLen + 1);
  strncpy(keyStr, line, keyLen);
  return strdup(keyStr);
}

char * getVal(char * line, size_t keyLen) {
  size_t valLen = strchr(line, '\n') - strchr(line, '=') - 1;
  char valStr[valLen + 1];
  memset(valStr, '\0', valLen + 1);
  strncpy(valStr, (line + keyLen + 1), valLen);
  return strdup(valStr);
}

kvarray_t * readKVs(const char * fname) {
  //WRITE ME
  FILE * f = fopen(fname, "r");
  if(f == NULL) {
    fprintf(stderr, "problem opening the file\n");
    exit(EXIT_FAILURE);
  }

  kvarray_t * kvArray = malloc(sizeof(kvarray_t));
  kvArray->nPairs = 0;
  kvArray->pairs = NULL;
  
  char * line = NULL;
  size_t lineSize = 0;
  size_t i = 0;
  char * curKey = NULL;
  char * curVal = NULL;

  while(getline(&line, &lineSize, f) > 0) {
    kvArray->nPairs++;
    i = kvArray->nPairs - 1;

    curKey = getKey(line);
    curVal = getVal(line, strlen(curKey));

    kvArray->pairs = realloc(kvArray->pairs, (kvArray->nPairs) * sizeof(kvpair_t*));

    kvArray->pairs[i] = malloc(sizeof(kvpair_t));
    kvArray->pairs[i]->key = strdup(curKey);
    kvArray->pairs[i]->val = strdup(curVal);

    free(curKey);
    free(curVal);
  }

  free(line);

  if(fclose(f) != 0) {
    fprintf(stderr, "problem closing the file\n");
    exit(EXIT_FAILURE);
  }

  return kvArray;
}



void freeKVs(kvarray_t * pairs) {
  //WRITE ME
  for(size_t i = 0; i < pairs->nPairs; i++) {
    free(pairs->pairs[i]->key);
    free(pairs->pairs[i]->val);
    free(pairs->pairs[i]);
  }
  free(pairs->pairs);
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  //WRITE ME
  char * key;
  char * val;
  for(size_t i = 0; i < pairs->nPairs; i++) {
    key = pairs->pairs[i]->key;
    val = pairs->pairs[i]->val;
    printf("key = '%s' value = '%s'\n", key, val);
  }
}


char * lookupValue(kvarray_t * pairs, const char * key) {
  //WRITE ME
  for(size_t i = 0; i < pairs->nPairs; i++) {
    if (strcmp(key, pairs->pairs[i]->key) == 0) {
      return ((pairs->pairs[i])->val);
    }
  }
  return NULL;
}
