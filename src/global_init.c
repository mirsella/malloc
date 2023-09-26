#include "../include/malloc.h"
#include <string.h>

/* t_mmap g_mmap = {NULL, NULL, ANCHOR, 0, NULL}; */
t_mmap *g_mmap = NULL;

pthread_mutex_t g_mutex = PTHREAD_MUTEX_INITIALIZER;

void lock_mutex() { pthread_mutex_lock(&g_mutex); }
void unlock_mutex() { pthread_mutex_unlock(&g_mutex); }

int tmpfd() {
  if (!LOGGING)
    return -1;
  static int fd = -2;
  if (fd == -2) {
    if ((fd = open(LOGFILE, O_WRONLY | O_CREAT | O_APPEND, 0666)) == -1) {
      ft_putstr_fd("malloc: open: ", STDERR_FILENO);
      ft_putstr_fd(strerror(errno), STDERR_FILENO);
    }
  }
  if (fd < 3)
    return STDOUT_FILENO;
  return fd;
}

/* void ft_strcat_nbr(char *dest, size_t nbr) { */
/*   int i; */
/**/
/*   i = 0; */
/*   if (nbr < 0) { */
/*     dest[ft_strlen(dest)] = '-'; */
/*     nbr = -nbr; */
/*   } */
/*   if (nbr > 9) { */
/*     ft_strcat_nbr(dest, nbr / 10); */
/*     ft_strcat_nbr(dest, nbr % 10); */
/*   } else { */
/*     dest[ft_strlen(dest)] = nbr + '0'; */
/*   } */
/* } */
/**/
/* void flog(char *title, size_t size) { */
/*   if (ft_strlen(title) + ft_nbrlen(size) >= 128) */
/*     return; */
/*   char buffer[128]; */
/*   ft_bzero(&buffer, 128); */
/*   ft_strlcpy(buffer, title, ft_strlen(title) + 1); */
/*   ft_strcat_nbr(buffer, size); */
/*   buffer[ft_strlen(buffer)] = '\n'; */
/*   ft_putstr_fd(buffer, tmpfd()); */
/* } */
