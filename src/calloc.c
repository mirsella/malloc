#include "../include/malloc.h"

void *calloc(size_t nmemb, size_t size) {
  size_t overflow = nmemb * size;
  if (size && overflow / size != nmemb) {
    if (LOGGING) {
      ft_dprintf(tmpfd(), "calloc(%d, %d): overflow\n", nmemb, size);
      /* flog("calloc: integer overflow", nmemb * size); */
    }
    return NULL;
  }

  size = nmemb * size;
  if (size == 0)
    size = 1;
  while (size % ALIGNMENT != 0)
    size++;
  if (LOGGING) {
    ft_dprintf(tmpfd(), "calloc(%d, %d)\n", nmemb, size);
    /* flog("calloc(): ", size * nmemb); */
  }
  lock_mutex();
  void *res = _malloc(size);
  unlock_mutex();
  if (res)
    ft_bzero(res, size);
  return res;
}
