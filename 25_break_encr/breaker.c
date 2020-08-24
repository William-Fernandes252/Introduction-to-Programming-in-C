#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int * frequencyCount(FILE * f) {
  int c;
  static int result[26] = {0};
  while((c = fgetc(f)) != EOF) {
    if(isalpha(c)) {
      ++result[c - 'a'];
    }
  }
  return result;
}

int findMostFrequentKey(int * freqArray) {
  int largeIdx = 0;
  for(size_t i = 0; i < 26; ++i) {
    if(freqArray[i] > freqArray[largeIdx]) {
      largeIdx = i;
    }
  }
  return largeIdx;
}

int main (int argc, char ** argv) {
  if(argc != 2) {
    fprintf(stderr, "Usage: decrypt inputFileName\n");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1], "r");
  if(f == NULL) {
    perror("Could not open file");
    return EXIT_FAILURE;
  }

  int * charFreq;
  charFreq = frequencyCount(f);

  int encryptedKey;
  encryptedKey = findMostFrequentKey(charFreq);

  unsigned key;

  if((encryptedKey >= 0) && (encryptedKey < 4)) {
    key = encryptedKey + 22;
  }
  else if((encryptedKey >= 4) && (encryptedKey < 26)) {
    key = encryptedKey - 4;
  }
  else {
    printf("Key out of range.\n");
    return EXIT_FAILURE;
  }

  printf("%d\n", key);

  return EXIT_SUCCESS;
}
