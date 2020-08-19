#include<stdio.h>
#include<stdlib.h>

size_t maxSeq(int * array, size_t n);

int main(void) {
  
  int array1[] = {};
  size_t ans1 = maxSeq(array1, 0);
  if(ans1 != 0) return EXIT_FAILURE;

  int array2[] = {1, 2, 1, 3, 5, 7, 2, 4, 6, 9};
  ans1 = maxSeq(array2, 10);
  if(ans1 != 4) return EXIT_FAILURE;

  /*int array3[] = {10, 10001, 10000002, -3999, -40, -4001, -4003, -4007, 1, 3, 4, 5, 6, 8};
  size_t ans2 = maxSeq(array3, 14);
  if(ans2 != 7) return EXIT_FAILURE;
  */
  /*int array4[] = {-300, -4, -3, -5, -6, -7, 3};
  size_t ans2 = maxSeq(array4, 7);
  if(ans2 != 3) return EXIT_FAILURE;
  */
  int array5[] = {1, 2, 2, 4}; 
  size_t ans2 = maxSeq(array5, 4);
  if(ans2 != 2) return EXIT_FAILURE;

  int array6[] = {1, 2, 3, 4}; 
  ans2 = maxSeq(array6, 4);
  if(ans2 != 4) return EXIT_FAILURE;

  int array7[] = {3, -4, 5, 6}; 
  ans2 = maxSeq(array7, 4);
  if(ans2 != 3) return EXIT_FAILURE;

  int array8[] = {10, 9, 7, 6}; 
  ans2 = maxSeq(array8, 4);
  if(ans2 != 1) return EXIT_FAILURE;
  
  return EXIT_SUCCESS;
}

