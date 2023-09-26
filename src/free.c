#include "../include/malloc.h"
#include <stddef.h>
#include <unistd.h>

void _free(void *ptr) {
  if (!ptr || TESTNULL(g_mmap))
    return;
  /* t_alloc *alloc = ptr - sizeof(t_alloc); */
  t_alloc *alloc = find_alloc_ptr(ptr);
  if (!alloc) {
    if (LOGGING) {
      ft_dprintf(tmpfd(), "free(%p): invalid pointer\n", ptr);
      /* flog("free: invalid pointer", (size_t)ptr); */
    }
    return;
  }
  if (alloc->prev)
    alloc->prev->next = alloc->next;
  if (alloc->next)
    alloc->next->prev = alloc->prev;
  if (alloc->parent->alloc == alloc)
    alloc->parent->alloc = alloc->next;

  // in case it's the only alloc in a t_mmap, free the mmap
  if (alloc->parent->type != LARGE)
    return;
  if (!alloc->next && !alloc->prev) {
    t_mmap *map = alloc->parent;
    if (map->prev)
      map->prev->next = map->next;
    if (map->next)
      map->next->prev = map->prev;
    // FIX: this cause page reclaims to skyrocket
    if (map == g_mmap)
      g_mmap = map->next;

    munmap(map, map->size + sizeof(t_mmap));
  }
}

void free(void *ptr) {
  if (LOGGING) {
    ft_dprintf(tmpfd(), "free(%p)\n", ptr);
    /* flog("free(): ", (size_t)ptr); */
  }
  if (!ptr)
    return;
  lock_mutex();
  _free(ptr);
  unlock_mutex();
}
