#include<stdio.h>
#include<stdlib.h>

size_t maxSeq (int * array, size_t n) {
  size_t lenght = 1;
  size_t result = 0;

  if(n == 0) {
    return 0;
  }
  
  for(int i = 1; i < n; i++) {
    if(array[i] > array[i - 1]) {
      lenght++;
    }
    else if(lenght > result) {
	result = lenght;
	lenght = 1;
    }
  }

  if(lenght > result) {
    result = lenght;
  }
  return result;
}
