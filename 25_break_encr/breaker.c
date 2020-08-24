#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int findKey(FILE * f) {
  int l;
  int frequency[26];
  char letters[] = {"abcdefghijklmnopqrstuvwxyz"};
  while((l = fgetc(f)) != EOF) {
    if(isalpha(l)) {
      l = tolower(l);
      char * p = strchr(letters, (char)l);
      int s = p - letters;
      frequency[s]++;
    }
  }
  int mostFrequentLetter = 0;
  for(int i = 0; i < 26; i++) {
    if(frequency[i] > mostFrequentLetter) {
      mostFrequentLetter = frequency[i];
    }
  }
  return mostFrequentLetter;
}

int breaker(FILE * f) {
  int c;
  int key = findKey(f);
  while((c = fgetc(f)) != EOF) {
    if(isalpha(c)) {
      c = tolower(c);
      c -= 'a';
      c += key;
      c %= 26;
      c += 'a';
    }
    printf("%c", c);
  }
  return key;
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

  int result = breaker(f);
  fprintf(stdout, "%d", result);
  return EXIT_SUCCESS;
}
