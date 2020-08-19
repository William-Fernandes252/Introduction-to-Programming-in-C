#include<stdio.h>
#include<stdlib.h>

size_t maxSeq (int * array, size_t n) {
  size_t length = 1;
  size_t result = 0;
  for(int i = 1; i < n; i++){
    if(array[i] > array[i - 1]){
      length++;
      if(lenght > result) {
	result = length;
    }
      else {
	length = 1;
  }
  return result;
}
