#include <../include/malloc.h>

void *reallocarray(void *ptr, size_t nmemb, size_t size) {
  // TODO: test overflow
  lock_mutex();
  // TODO: rsyslog()
  return _realloc(ptr, nmemb * size);
  unlock_mutex();
}
