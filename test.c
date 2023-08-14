#include "include/malloc.h"
#include <stdio.h>
#include <strings.h>
#include <unistd.h>
int main(void) {
  int len = 100;
  char *a = malloc(len);
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

  free(a);
  free(b);
  free(c);
  return EXIT_SUCCESS;
}
