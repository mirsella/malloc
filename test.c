#include "include/malloc.h"
#include "libft/libft.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  char *str = (char *)malloc(20);
  assert(str != NULL);
  ft_strlcpy(str, "42helloworld", 20);
  assert(strcmp(str, "42helloworld") == 0);
  ft_bzero(str, 20);
  free(str);

  int *arr = (int *)calloc(5, sizeof(int));
  assert(arr != NULL);
  for (int i = 0; i < 5; i++) {
    assert(arr[i] == 0);
  }
  ft_bzero(arr, 5 * sizeof(int));
  free(arr);

  char *dynstr = (char *)malloc(5);
  assert(dynstr != NULL);
  ft_strlcpy(dynstr, "Test", 5);
  dynstr = realloc(dynstr, 10);
  ft_strlcat(dynstr, "1234", 10);
  assert(ft_strcmp(dynstr, "Test1234") == 0);
  ft_bzero(dynstr, 10);
  free(dynstr);

  void *edge1 = malloc(0);
  free(edge1);

  char *edge2 = (char *)malloc(5);
  ft_bzero(edge2, 5);
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
