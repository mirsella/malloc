#include "../include/malloc.h"

t_mmap *g_mmap = NULL;

pthread_mutex_t g_mutex = PTHREAD_MUTEX_INITIALIZER;

void lock_mutex() { pthread_mutex_lock(&g_mutex); }
void unlock_mutex() { pthread_mutex_unlock(&g_mutex); }

int tmpfd() {
  if (!LOGGING)
    return -1;
  static int fd = -2;
  if (fd == -2) {
    if ((fd = open(LOGFILE, O_WRONLY | O_CREAT, 0666)) == -1) {
      dprintf(STDERR_FILENO, "malloc: open: %s\n", strerror(errno));
    }
  }
  if (fd < 3)
    return STDOUT_FILENO;
  return fd;
}
