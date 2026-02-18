#include "TwoNumberSum.h"

#define ARRAY_LEN(x) (sizeof(x) / sizeof((x)[0]))

int main() {
  int numArray[] = {3, 5, -4, 8, 11, 1, -1, 6};

  size_t length = ARRAY_LEN(numArray);

  TwoNumberSum(numArray, length, 10);

  return 0;
}
