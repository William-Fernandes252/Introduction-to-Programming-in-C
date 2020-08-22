#include<stdio.h>
#include<stdlib.h>

unsigned power(unsigned x, unsigned y);

int main(void) {

  unsigned x = 0;
  unsigned y = 0;
  unsigned ans = power(x, y);
  if(ans != 1) return EXIT_FAILURE;

  x = 4;
  y = 1;
  ans = power(x, y);
  if(ans != 4) return EXIT_FAILURE;

  x = 4;
  y = 4;
  ans = power(x, y);
  if(ans != 256) return EXIT_FAILURE;

  x = 88888657;
  y = 0;
  ans = power(x, y);
  if(ans != 1) return EXIT_FAILURE;

  x = 1;
  y = 999999988;
  ans = power(x, y);
  if(ans != 1) return EXIT_FAILURE;

  x = 9999998;
  y = 1;
  ans = power(x, y);
  if(ans != 9999998) return EXIT_FAILURE;

  x = 0;
  y = 999999999;
  ans = power(x, y);
  if(ans != 0) return EXIT_FAILURE;

  x = 1;
  y = 1;
  ans = power(x, y);
  if(ans != 1) return EXIT_FAILURE;

  x = 65535;
  y = 2;
  ans = power(x, y);
  if(ans != 4294836225) return EXIT_FAILURE;

  x = 49;
  y = 4;
  ans = power(x, y);
  if(ans != 5764801) return EXIT_FAILURE;

  x = 9;
  y = 10;
  ans = power(x, y);
  if(ans != 3486784401) return EXIT_FAILURE;
  
  return EXIT_SUCCESS;
}
