#include "../include/malloc.h"

void _free(void *ptr) {
  if (!ptr)
    return;
  if (!g_mmap)
    return;
  /* t_alloc *alloc = ptr - sizeof(t_alloc); */
  t_alloc *alloc = find_alloc_ptr(ptr);
  if (!alloc) {
    // ft_printf("tryed _free(%p) but it's not an alloc\n", ptr);
    // TODO: rsyslog()
    return;
  }
  if (alloc->prev)
    alloc->prev->next = alloc->next;
  if (alloc->next)
    alloc->next->prev = alloc->prev;
  if (alloc->parent->alloc == alloc)
    alloc->parent->alloc = alloc->next;

  // in case it's the only alloc in a t_mmap, free the mmap
  if (!alloc->next && !alloc->prev) {
    t_mmap *map = alloc->parent;
    if (map->prev)
      map->prev->next = map->next;
    if (map->next)
      map->next->prev = map->prev;
    if (map == g_mmap)
      g_mmap = map->next;
  }
}

void free(void *ptr) {
  // ft_printf("free(%p)\n", ptr);
  if (!ptr)
    return;
  // TODO: rsyslog()
  lock_mutex();
  _free(ptr);
  unlock_mutex();
}
