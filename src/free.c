#include "../include/malloc.h"

void _free(void *ptr) {
  // TODO: free ptr
  ft_printf("freeing %p\n", ptr);
}

void free(void *ptr) {
  if (!ptr)
    return;
  lock_mutex();
  // TODO: rsyslog()
  _free(ptr);
  unlock_mutex();
}
