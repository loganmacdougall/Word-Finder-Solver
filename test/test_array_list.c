#include "test_array_list.h"
#include "tester.h"

int data[] = {1, 2, 3, 4, 5};

void test_init() {
  ArrayList *list = arraylist_init(sizeof(int));
  assert_not_null(list);
  arraylist_destroy(list);
}

void test_push_pop_back() {
  ArrayList *list = arraylist_init(sizeof(int));
  assert_not_null(list);

  assert_equal(arraylist_length(list), 0);
  arraylist_push_back(list, &data[0]);
  arraylist_push_back(list, &data[1]);
  assert_equal(arraylist_length(list), 2);
  arraylist_push_back(list, &data[2]);
  arraylist_push_back(list, &data[3]);
  arraylist_push_back(list, &data[4]);
  assert_equal(arraylist_length(list), 5);

  int *element;

  for (int i = 4; i >= 0; i--) {
    assert_equal(arraylist_length(list), i + 1);
    element = arraylist_pop_back(list);
    assert_equal(data[i], *element);
  }
  assert_equal(arraylist_length(list), 0);

  arraylist_destroy(list);
}

void test_push_pop_front() {
  ArrayList *list = arraylist_init(sizeof(int));
  assert_not_null(list);

  assert_equal(arraylist_length(list), 0);
  arraylist_push_front(list, &data[0]);
  arraylist_push_front(list, &data[1]);
  assert_equal(arraylist_length(list), 2);
  arraylist_push_front(list, &data[2]);
  arraylist_push_front(list, &data[3]);
  arraylist_push_front(list, &data[4]);
  assert_equal(arraylist_length(list), 5);

  int *element;

  for (int i = 4; i >= 0; i--) {
    assert_equal(arraylist_length(list), i + 1);
    element = arraylist_pop_front(list);
    assert_equal(data[i], *element);
  }
  assert_equal(arraylist_length(list), 0);

  arraylist_destroy(list);
}

void test_array_get_set() {
  ArrayList *list = arraylist_init(sizeof(int));
  assert_not_null(list);

  arraylist_push_back(list, &data[0]);
  arraylist_push_back(list, &data[1]);
  arraylist_push_back(list, &data[2]);
  arraylist_push_back(list, &data[3]);
  arraylist_push_back(list, &data[4]);

  int *elem;
  for (int i = 0; i < 5; i++) {
    elem = arraylist_get(list, i);
    assert_equal(*elem, data[i]);
    *elem = *elem * 2 + 3;
    arraylist_set(list, elem, i);
    free(elem);
  }

  for (int i = 0; i < 5; i++) {
    elem = arraylist_get(list, i);
    assert_equal(*elem, data[i] * 2 + 3);
  }

  arraylist_destroy(list);
}

void test_swap() {
  ArrayList *list = arraylist_init(sizeof(int));
  assert_not_null(list);

  arraylist_push_back(list, &data[0]);
  arraylist_push_back(list, &data[1]);
  arraylist_push_back(list, &data[2]);
  arraylist_push_back(list, &data[3]);
  arraylist_push_back(list, &data[4]);

  // 1, 2, 3, 4, 5
  arraylist_swap(list, 0, 3); // 4, 2, 3, 1, 5
  arraylist_swap(list, 1, 4); // 4, 5, 3, 1, 2
  arraylist_swap(list, 2, 3); // 4, 5, 1, 3, 2

  assert_equal(*(int *)list->data[0], 4);
  assert_equal(*(int *)list->data[1], 5);
  assert_equal(*(int *)list->data[2], 1);
  assert_equal(*(int *)list->data[3], 3);
  assert_equal(*(int *)list->data[4], 2);
}

void run_testcases() {
  printf("Testing arraylist Initialize...\n");
  test_init();
  printf("Passed!\nTesting arraylist push and pop from back...\n");
  test_push_pop_back();
  printf("Passed!\nTesting arraylist push and pop from front...\n");
  test_push_pop_front();
  printf("Passed!\nTesting arraylist get and set...\n");
  test_array_get_set();
  printf("Passed!\nTesting arraylist swap...\n");
  test_swap();
  printf("Passed!\n");
}
