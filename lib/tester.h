#ifndef __HEADER_TESTER
#define __HEADER_TESTER

#include <stdio.h>
#include <stdlib.h>

#define assert_true(COND)                                                      \
  if (!(COND)) {                                                               \
    fprintf(stderr, "Assert Failed:\nConditional %s should be true\n", #COND); \
    exit(EXIT_FAILURE);                                                        \
  }

#define assert_false(COND)                                                     \
  if (COND) {                                                                  \
    fprintf(stderr, "Assert Failed:\nConditional %s should be false\n",        \
            #COND);                                                            \
    exit(EXIT_FAILURE);                                                        \
  }

#define assert_not_null(PTR)                                                   \
  if (PTR == NULL) {                                                           \
    fprintf(stderr, "Assert Failed:\nPtr %s should not be NULL\n", #PTR);      \
    exit(EXIT_FAILURE);                                                        \
  }

#define assert_null(PTR)                                                       \
  if (PTR != NULL) {                                                           \
    fprintf(stderr, "Assert Failed:\nPTR %s should be NULL\n", #PTR);          \
    exit(EXIT_FAILURE);                                                        \
  }

#define assert_equal(E1, E2)                                                   \
  if ((E1) != (E2)) {                                                          \
    fprintf(stderr, "Assert Failed:\n%s and %s should be equal\n", #E1, #E2);  \
    exit(EXIT_FAILURE);                                                        \
  }

#define assert_not_equal(E1, E2)                                               \
  if ((E1) == (E2)) {                                                          \
    fprintf(stderr, "Assert Failed:\n%s and %s should not be equal\n", #E1,    \
            #E2);                                                              \
    exit(EXIT_FAILURE);                                                        \
  }

#endif
