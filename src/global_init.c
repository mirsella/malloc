#include "../include/malloc.h"

t_mmap *g_mmap = NULL;

pthread_mutex_t *get_mutex() {
  static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
  return &mutex;
}

void lock_mutex() { pthread_mutex_lock(get_mutex()); }
void unlock_mutex() { pthread_mutex_unlock(get_mutex()); }
