#include "../include/malloc.h"

void *_malloc(size_t size) {
  size += ALIGNMENT;
  t_alloc *res = find_alloc(size);
  if (res)
    return alignp(ALLOC_SHIFT(res));
  new_mmap(size - ALIGNMENT);
  res = find_alloc(size);
  if (!res)
    return NULL;
  return alignp(ALLOC_SHIFT(res));
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
  if (!res)
    ft_printf("malloc returned null\n");
  return res;
}
