#include "../include/malloc.h"

void *_calloc(size_t nmemb, size_t size) {
  // TODO: test overflow
  // TODO: ask for size bytes of memory
  // TODO: bzero it
  return NULL;
}

void *calloc(size_t nmemb, size_t size) {
  if (nmemb * size == 0)
    return NULL;
  lock_mutex();
  // TODO: rsyslog()
  char *res = _calloc(nmemb, size);
  unlock_mutex();
  return res;
}
