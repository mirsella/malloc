#include "../include/malloc.h"

t_mmap *g_mmap = NULL;

pthread_mutex_t g_mutex = PTHREAD_MUTEX_INITIALIZER;

void lock_mutex() { pthread_mutex_lock(&g_mutex); }
void unlock_mutex() { pthread_mutex_unlock(&g_mutex); }

void ft_strcat_nbr(char *dest, size_t nbr) {
  int i;

  i = 0;
  if (nbr < 0) {
    dest[ft_strlen(dest)] = '-';
    nbr = -nbr;
  }
  if (nbr > 9) {
    ft_strcat_nbr(dest, nbr / 10);
    ft_strcat_nbr(dest, nbr % 10);
  } else {
    dest[ft_strlen(dest)] = nbr + '0';
  }
}

// TODO: test this
void log(int priority, char *title, size_t size) {
  if (ft_strlen(title) + ft_nbrlen(size) >= 500)
    return;
  char buffer[512];
  ft_bzero(&buffer, 128);
  ft_strlcpy(buffer, title, ft_strlen(title) + 1);
  ft_strcat_nbr(buffer, size);
}
