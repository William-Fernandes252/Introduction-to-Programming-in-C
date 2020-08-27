#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "outname.h"

char * computeOutputFileName(const char * inputName) {
  char * outputName = malloc((strlen(inputName) + 4) * sizeof(outputName));
  char counts[] = ".counts";
  strcpy(outputName, inputName);
  strcat(outputName, counts);
  return outputName;
}
