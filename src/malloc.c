#include "../include/malloc.h"
#include <stdio.h>

void *_malloc(size_t size) {
  void *res;
  if (g_mmap && (res = find_alloc(size)))
    return ALLOC_SHIFT(res);
  t_mmap *t_mmap = mmap(NULL, get_mmap_size(size), PROT_READ | PROT_WRITE,
                        MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
  if (!t_mmap)
    return NULL;
  if (!g_mmap) {
    g_mmap = t_mmap;
    t_mmap->next = t_mmap;
    t_mmap->prev = t_mmap;
  } else {
    g_mmap->prev->next = t_mmap;
    t_mmap->prev = g_mmap->prev;
    t_mmap->next = g_mmap;
    g_mmap->prev = t_mmap;
  }
  t_mmap->type = get_mmap_type(size);
  t_mmap->size = get_mmap_size(size);
  t_mmap->alloc = NULL;
  return ALLOC_SHIFT(find_alloc(size));
}

void *malloc(size_t size) {
  ft_putstr("calling ft_malloc");
  if (size == 0)
    return NULL;
  lock_mutex();
  // TODO: rsyslog()
  void *res = _malloc(size);
  unlock_mutex();
  return res;
}
