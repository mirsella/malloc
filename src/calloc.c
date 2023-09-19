#include "../include/malloc.h"

void *calloc(size_t nmemb, size_t size) {
  size_t overflow = nmemb * size;
  if (size && overflow / size != nmemb) {
    if (LOGGING)
      dprintf(tmpfd(), "calloc(%zu, %zu): overflow\n", nmemb, size);
    return NULL;
  }

  if (nmemb * size == 0)
    size = 1;
  while (size % ALIGNMENT != 0)
    size++;
  if (LOGGING)
    dprintf(tmpfd(), "calloc(%zu, %zu)\n", nmemb, size);
  lock_mutex();
  void *res = _malloc(nmemb * size);
  unlock_mutex();
  ft_bzero(res, nmemb * size);
  return res;
}
