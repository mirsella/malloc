#include "include/malloc.h"
#include <stdio.h>
#include <strings.h>
#include <unistd.h>
int main(void) {
  int len = 100;
  char *a = malloc(len);
  ft_printf("a(%p)\n", a);
  ft_bzero(a, len);
  char *a1 = malloc(len);
  ft_bzero(a1, len);
  ft_printf("a(%p)\n", a1);
  a = malloc(len);
  ft_printf("a(%p)\n", a);
  ft_bzero(a, len);
  free(a1);
  a = malloc(len);
  ft_printf("a(%p)\n", a);
  ft_bzero(a, len);

  len = 4000;
  char *b = malloc(len);
  ft_printf("b(%p)\n", b);
  ft_bzero(b, len);

  len = 500;
  char *c = malloc(len);
  ft_printf("c(%p)\n", c);
  ft_bzero(c, len);

  /* ft_printf("allocating 1000 times\n"); */
  /* for (int i = 0; i < 1000; i++) { */
  /*   char *d = malloc(i); */
  /*   ft_bzero(d, i); */
  /* } */

  ft_putchar('\n');
  show_alloc_mem();
  return EXIT_SUCCESS;
}
