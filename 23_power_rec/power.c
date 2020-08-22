#include<stdio.h>
#include<stdlib.h>

unsigned power (unsigned x, unsigned y) {

  if((x == 0 && y == 0) || y == 1) {
    return 1;
  }

  if(x == 0) {
    return 0;
  }

  unsigned ans = x * x;
  unsigned helper = y - 1;

  return ans * power(ans, helper);
}