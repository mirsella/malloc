#include "../include/malloc.h"

void *reallocarray(void *ptr, size_t nmemb, size_t size) {
  size_t overflow = nmemb * size;
  if (size && overflow / size != nmemb) {
    // TODO: rsyslog() detected overflow
    return NULL;
  }
  if (nmemb * size == 0)
    return NULL;
  lock_mutex();
  // TODO: rsyslog()
  void *res = _realloc(ptr, nmemb * size);
  unlock_mutex();
  return res;
}
