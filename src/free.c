#include "../include/malloc.h"

// alternative method to find alloc even if the ptr is in the middle of the
// alloc
t_alloc *find_alloc_ptr(void *ptr) {
  for (t_mmap *mmap = g_mmap; mmap; mmap = mmap->next) {
    if (ptr < (void *)mmap || ptr > MMAP_SHIFT(mmap) + mmap->size)
      continue;
    for (t_alloc *alloc = mmap->alloc; alloc; alloc = alloc->next) {
      if (ptr > ALLOC_SHIFT(alloc) + alloc->size)
        continue;
      if (ptr < (void *)alloc)
        return NULL;
      if (ptr < ALLOC_SHIFT(alloc) + alloc->size && ptr >= ALLOC_SHIFT(alloc))
        return alloc;
      return NULL;
    }
  }
  return NULL;
}

void _free(void *ptr) {
  if (!ptr)
    return;
  if (!g_mmap)
    return;
  t_alloc *alloc = ptr - sizeof(t_alloc);
  /* t_alloc *alloc = find_alloc_ptr(ptr); */
  if (!alloc) {
    ft_printf("tryed _free(%p) but it's not an alloc\n", ptr);
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
  ft_printf("free(%p)\n", ptr);
  if (!ptr)
    return;
  // TODO: rsyslog()
  lock_mutex();
  _free(ptr);
  unlock_mutex();
}
