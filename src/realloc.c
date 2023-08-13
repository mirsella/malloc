#include "../include/malloc.h"

void *_realloc(void *ptr, size_t size) {
  // TODO: try to shrink or extend the block pointed to by ptr to size
  // TODO: if not possible, allocate a new block of size bytes. copy as much
  // data to new location. free old one.
  (void)ptr;
  (void)size;
  return NULL;
}

void *realloc(void *ptr, size_t size) {

  lock_mutex();
  // TODO: rsyslog()
  void *res = NULL;
  if (!ptr)
    res = _malloc(size);
  else if (!size && ptr)
    _free(ptr);
  else
    res = _realloc(ptr, size);
  unlock_mutex();
  return res;
}
