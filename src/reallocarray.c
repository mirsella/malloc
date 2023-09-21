#include "../include/malloc.h"
#include <stddef.h>

void *reallocarray(void *ptr, size_t nmemb, size_t size) {
  size_t overflow = nmemb * size;
  if (size && overflow / size != nmemb) {
    if (LOGGING) {
      ft_dprintf(tmpfd(), "reallocarray(%p, %d, %d): overflow\n", ptr, nmemb,
                 size);
      /* flog("reallocarray(): integer overflow", (size_t)ptr); */
    }
    errno = ENOMEM;
    return NULL;
  }
  if (nmemb * size == 0)
    size = 1;
  while (size % ALIGNMENT != 0)
    size++;
  if (LOGGING) {
    ft_dprintf(tmpfd(), "reallocarray(%p, %d, %d)\n", ptr, nmemb, size);
    /* flog("reallocarray(): ", (size_t)ptr); */
  }
  void *res = NULL;
  lock_mutex();
  if (!ptr)
    res = _malloc(size * nmemb);
  else if ((size * nmemb) == 0 && ptr)
    _free(ptr);
  else
    res = _realloc(ptr, size * nmemb);
  unlock_mutex();
  return res;
}
