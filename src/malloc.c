#include "../include/malloc.h"

void *_malloc(size_t size) {
  void *res = find_alloc(size);
  if (res)
    return ALLOC_SHIFT(res);
  new_mmap(size);
  res = find_alloc(size);
  return res;
}

void *malloc(size_t size) {
  ft_printf("malloc(%d)\n", size);
  if (size == 0)
    return NULL;
  lock_mutex();
  // TODO: rsyslog()
  void *res = _malloc(size);
  unlock_mutex();
  return res;
}
