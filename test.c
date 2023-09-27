#include "include/malloc.h"
#include "libft/libft.h"
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

  void *edge1 = malloc(0);
  free(edge1);

  char *edge2 = (char *)malloc(5);
  edge2 = realloc(edge2, 0);
  assert(edge2 == NULL);

  ft_printf("All tests passed!\n");

  void *a = malloc(10);
  ft_memcpy(a, "0123456789", 10);
  void *b = malloc(4000);
  ft_memset(b, 'i', 4000);
  void *c = malloc(1000);
  ft_memset(c, 'a', 1000);
  ft_putchar('\n');
  show_alloc_mem();
  ft_putchar('\n');
  show_alloc_mem_hexdump();
  ft_putchar('\n');
  show_alloc_mem_asciidump();
  free(a);
  free(b);
  free(c);
  return EXIT_SUCCESS;
}
