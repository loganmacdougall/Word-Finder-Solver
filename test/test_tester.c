#include "tester.h"

int main() {
  int a = 1;
  int b = 2;
  int c = 3;

  assert_true(a + b == c);
  assert_false(a - b == c);
  assert_equal(a + b, c);
  assert_not_equal(a - b, c);

  printf("All tests passed\n");

  return 0;
}
