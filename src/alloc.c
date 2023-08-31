#include "../include/malloc.h"

t_alloc *new_alloc(t_mmap *mmap, void *ptr, size_t size) {
  t_alloc *alloc = ptr;
  alloc->size = size;
  alloc->parent = mmap;
  /* ft_printf("creating new alloc at %p. should return %p\n", ptr, */
  /* ALLOC_SHIFT(ptr)); */
  alloc->next = NULL;
  alloc->prev = NULL;

  if (!mmap->alloc)
    return mmap->alloc = alloc;
  for (t_alloc *tmp = mmap->alloc; tmp; tmp = tmp->next) {
    if (alloc < tmp) {
      alloc->next = tmp;
      alloc->prev = tmp->prev;
      tmp->prev = alloc;
      if (alloc->prev)
        alloc->prev->next = alloc;
      if (mmap->alloc == tmp)
        mmap->alloc = alloc;
      break;
    } else if (alloc > tmp && (alloc < tmp->next || !tmp->next)) {
      alloc->next = tmp->next;
      alloc->prev = tmp;
      tmp->next = alloc;
      if (alloc->next)
        alloc->next->prev = alloc;
      break;
    }
  }
  return alloc;
}

t_alloc *find_alloc(size_t size) {
  if (!g_mmap)
    return NULL;
  for (t_mmap *mmap = g_mmap; mmap; mmap = mmap->next) {
    if (mmap->type != get_mmap_type(size))
      continue;

    // in case it's the first allocation of a mmap
    if (!mmap->alloc)
      return new_alloc(mmap, MMAP_SHIFT(mmap), size);

    t_alloc *alloc = mmap->alloc;
    void *ptr = MMAP_SHIFT(mmap);
    while (alloc) { // seach for space between allocated spaces
      size_t space = (void *)alloc - ptr;
      if (ptr < (void *)alloc && space >= (size_t)ALLOC_SHIFT(size))
        return new_alloc(mmap, ptr, size);

      ptr = ALLOC_SHIFT(alloc) + alloc->size;
      alloc = alloc->next;
    }
    // allocated space after the last allocated space
    if ((void *)(MMAP_SHIFT(mmap) + mmap->size - ptr) >= ALLOC_SHIFT(size))
      return new_alloc(mmap, ptr, size);
  }
  return NULL;
}
