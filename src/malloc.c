#include "../include/malloc.h"

void *_malloc(size_t size) {
  // TODO: ask for size bytes of memory
  return NULL;
}

void *malloc(size_t size) {
  if (size == 0)
    return NULL;
  lock_mutex();
  // TODO: rsyslog()
  void *res = _malloc(size);
  unlock_mutex();
  return res;
}
