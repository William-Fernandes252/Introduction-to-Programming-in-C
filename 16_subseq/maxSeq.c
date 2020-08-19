#include<stdio.h>
#include<stdlib.h>

size_t maxSeq (int * array, size_t n) {

  size_t lenght = 1;
  size_t result = 1;

  if(n == 0) {
    return 0;
  }
  
  for(size_t i = 1; i < n; i++) {
    if(array[i] > array[i - 1]) {
      lenght += 1;
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
