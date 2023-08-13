#include "../include/malloc.h"

void *calloc(size_t nmemb, size_t size) {
	size_t overflow = nmemb * size;
	if (size && overflow / size != nmemb) {
    // TODO: rsyslog() detected overflow
    return NULL;
  }
  if (nmemb * size == 0)
    return NULL;
  lock_mutex();
  // TODO: rsyslog()
  void *res = _malloc(nmemb * size);
  unlock_mutex();
  ft_bzero(res, nmemb * size);
  return res;
}
