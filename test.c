#include "include/malloc.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  // 1. Basic functionality tests
  char *str = (char *)malloc(20);
  assert(str != NULL);
  strcpy(str, "42helloworld");
  assert(strcmp(str, "42helloworld") == 0);
  free(str);

  int *arr = (int *)calloc(5, sizeof(int));
  assert(arr != NULL);
  for (int i = 0; i < 5; i++) {
    assert(arr[i] == 0);
  }
  free(arr);

  char *dynstr = (char *)malloc(5);
  assert(dynstr != NULL);
  strcpy(dynstr, "Test");
  dynstr = realloc(dynstr, 10);
  strcat(dynstr, "1234");
  assert(strcmp(dynstr, "Test1234") == 0);
  free(dynstr);

  // 2. Memory integrity tests
  int *numbers = (int *)malloc(10 * sizeof(int));
  assert(numbers != NULL);
  for (int i = 0; i < 10; i++) {
    numbers[i] = i;
  }
  for (int i = 0; i < 10; i++) {
    assert(numbers[i] == i);
  }
  free(numbers);

  char *buf1 = (char *)malloc(100);
  char *buf2 = (char *)malloc(100);
  for (int i = 0; i < 100; i++) {
    buf1[i] = 1;
    buf2[i] = 2;
  }
  for (int i = 0; i < 100; i++) {
    assert(buf1[i] == 1);
    assert(buf2[i] == 2);
  }
  free(buf1);
  free(buf2);

  // 3. Edge cases
  void *edge1 = malloc(0);
  free(edge1); // This should not crash

  char *edge2 = (char *)malloc(5);
  edge2 = realloc(edge2, 0); // This should behave as free
  assert(edge2 == NULL);

  printf("All tests passed!\n");
  return EXIT_SUCCESS;
}
