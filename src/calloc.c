#include "../include/malloc.h"

void *calloc(size_t nmemb, size_t size) {
  // TODO: test overflow
  if (nmemb * size == 0)
    return NULL;
  lock_mutex();
  // TODO: rsyslog()
  void *res = _malloc(nmemb * size);
  unlock_mutex();
  return res;
}
