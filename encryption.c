#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void encrypt(FILE * f, int key) {
  int c;
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
}

int main(int argc, char ** argv) {
  if(argc != 3) {
    printf("Usage: encrypt key inputFileName\n");
    return EXIT_FAILURE;
  }

  int key = atoi(argv[1]);
  if (key == 0) {
    printf("Invalid key (%s): must be a non-zero integer\n", argv[1]);
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[2], "r");
  if(f == NULL) {
    perror("Could not open the file");
    return EXIT_FAILURE;
  }
  encrypt(f, key);

  if(fclose(f) != 0) {
    printf("Failed to close the input file!");
  }

  return EXIT_SUCCESS;
}
