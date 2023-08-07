#include "../include/malloc.h"

void *_malloc(size_t size) {
  (void)g_mmap;
  (void)size;
  ft_printf("addr g_mmap %p\n", g_mmap);
  return NULL;
}

void *malloc(size_t size) {
  lock_mutex();
  // TODO: rsyslog()
  char *res = _malloc(size);
  unlock_mutex();
  return res;
}
