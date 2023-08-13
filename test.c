#include "include/malloc.h"
#include <stdio.h>
int main(void) {
  int len = 10;
  char *a = malloc(len);
  a = malloc(len);
  if (!a)
    printf("a is NULL");
  for (int i = 0; i < len; i++) {
    a[i] = 'a' + i;
  }
  write(1, a, len);
  return EXIT_SUCCESS;
}
