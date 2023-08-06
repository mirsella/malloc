#include "../include/malloc.h"
void *_malloc(size_t size) {}

void *malloc(size_t size) {
  lock_mutex();
  // TODO: rsyslog()
  char *res = _malloc(size);
  unlock_mutex();
  return res;
}
