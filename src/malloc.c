#include "../include/malloc.h"

void *_malloc(size_t size) {
  t_alloc *res = find_alloc(size);
  if (res)
    return ALLOC_SHIFT(res);
  new_mmap(size);
  res = find_alloc(size);
  return ALLOC_SHIFT(res);
}

void *malloc(size_t size) {
  ft_printf("malloc(%d)", size);
  /* if (size == 0) */
  /*   return NULL; */
  lock_mutex();
  // TODO: rsyslog()
  void *res = _malloc(size);
  unlock_mutex();
  ft_printf(" -> %p\n", res);
  return res;
}
