//Create and initialize a array with the lenght entered by the user

#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

int * iniArray(int howLarge) {
  int * array = malloc(howLarge * sizeof(array));
  if(array == NULL) {
    exit(EXIT_FAILURE);
  }
  for(size_t i = 0; i < howLarge; i++) {
    array[i] = i + 1;
  }
  return array;
}

int main(void) {
  int lenght = 0;
  scanf("%d", &lenght);

  int * p = iniArray(lenght);

  for(size_t i = 0; i < lenght; i++) {
    printf("%-2d", p[i]);
  }
  printf("\n");

  return EXIT_SUCCESS;
}
