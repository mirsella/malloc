#include "../include/malloc.h"
#include <unistd.h>

void *_malloc(size_t size) {
  t_alloc *res = find_alloc(size);
  if (res)
    return ALLOC_SHIFT(res);
  if (!new_mmap(size))
    return NULL;
  res = find_alloc(size);
  return ALLOC_SHIFT(res);
}

void *malloc(size_t size) {
  if (LOGGING) {
    ft_dprintf(tmpfd(), "malloc(%d)\n", size);
    /* flog("malloc(): ", size); */
  }
  if (!size)
    size = 1;
  while (size % ALIGNMENT != 0)
    size++;
  lock_mutex();
  void *res = _malloc(size);
  unlock_mutex();
  return res;
}
