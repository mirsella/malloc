#include "../include/malloc.h"

void *reallocarray(void *ptr, size_t nmemb, size_t size) {
  /* ft_printf("reallocarray(%d) on %p", size * nmemb, ptr); */
  size_t overflow = nmemb * size;
  if (size && overflow / size != nmemb) {
    // TODO: rsyslog() detected overflow
    ft_printf("OVERFLOW");
    errno = ENOMEM;
    return NULL;
  }
  if (nmemb * size == 0)
    size = 1;
  while (size % ALIGNMENT != 0)
    size++;
  /* return NULL; */
  // TODO: rsyslog()
  void *res;
  lock_mutex();
  if (!ptr)
    res = _malloc(size * nmemb);
  else if ((size * nmemb) == 0 && ptr)
    _free(ptr);
  else
    res = _realloc(ptr, size * nmemb);
  unlock_mutex();
  /* ft_printf(" -> %p\n", res); */
  return res;
}
