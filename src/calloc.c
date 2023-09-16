#include "../include/malloc.h"

void *calloc(size_t nmemb, size_t size) {
  /* ft_printf("calloc(%d)", size); */
  size_t overflow = nmemb * size;
  if (size && overflow / size != nmemb) {
    ft_printf("OVERFLOW\n");
    //   TODO: rsyslog() detected overflow
    return NULL;
  }

  if (nmemb * size == 0)
    size = 1;
  while (size % ALIGNMENT != 0)
    size++;
  // TODO: rsyslog()
  lock_mutex();
  void *res = _malloc(nmemb * size);
  unlock_mutex();
  ft_bzero(res, nmemb * size);
  /* ft_printf(" -> %p\n", res); */
  return res;
}
