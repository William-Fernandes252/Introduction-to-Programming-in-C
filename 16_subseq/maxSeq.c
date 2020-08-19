#include<stdio.h>
#include<stdlib.h>

size_t maxSeq (int * array, size_t n) {
  size_t length = 1;
  size_t result = 0;

  if(n == 0) {
    return 0;
  }
  
  for(int i = 1; i < n; i++) {
    if(pArray[i] > pArray[i - 1]) {
      length++;
    }
    else if(length > result) {
	result = length;
	lenght = 1;
    }
  }

  if(lenght > result) {
    result = lenght;
  }
  return result;
}
