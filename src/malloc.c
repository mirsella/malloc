#include "../include/malloc.h"

void *_malloc(size_t size) {
  t_alloc *res = find_alloc(size);
  if (res)
    return ALLOC_SHIFT(res);
  new_mmap(size);
  res = find_alloc(size);
  if (!res)
    ft_printf("NO SPACE FOUND ON NEW MMAP\n");
  return ALLOC_SHIFT(res);
}

void *malloc(size_t size) {
  ft_printf("malloc(%d)", size);
  if (!size)
    return NULL;
  // TODO: rsyslog()
  lock_mutex();
  void *res = _malloc(size);
  unlock_mutex();
  ft_printf(" -> %p\n", res);
  return res;
}
