#include "../include/malloc.h"

// alternative method to find alloc even if the ptr is in the middle of the
// alloc
t_alloc *find_alloc_ptr(void *ptr) {
  if (TESTNULL(g_mmap))
    return NULL;
  for (t_mmap *mmap = g_mmap; !TESTNULL(mmap); mmap = mmap->next) {
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

void *alignp(void *size) {
  intptr_t s = (intptr_t)size;
  while (s % ALIGNMENT != 0)
    s++;
  return (void *)s;
}

t_alloc *new_alloc(t_mmap *mmap, void *ptr, size_t size) {
  t_alloc *alloc = ptr;
  alloc->size = size;
  alloc->parent = mmap;
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
  if (TESTNULL(g_mmap))
    return NULL;
  for (t_mmap *mmap = g_mmap; !TESTNULL(mmap); mmap = mmap->next) {
    if (mmap->type != get_mmap_type(size))
      continue;

    // in case it's the first allocation of a mmap
    if (!mmap->alloc)
      return new_alloc(mmap, alignp(MMAP_SHIFT(mmap)), size);

    t_alloc *alloc = mmap->alloc;
    void *ptr = alignp(MMAP_SHIFT(mmap));
    // + ALIGNMENT because we need to have space to align the alloc
    size_t needed_space = size + sizeof(t_alloc) + ALIGNMENT;
    while (alloc) { // seach for space between allocated spaces
      size_t space = (void *)alloc - ptr;
      if (ptr < (void *)alloc && space >= needed_space)
        return new_alloc(mmap, ptr, size);

      ptr = alignp(ALLOC_SHIFT(alloc) + alloc->size);
      alloc = alloc->next;
    }
    // allocated space after the last allocated space
    if ((size_t)(MMAP_SHIFT(mmap) + mmap->size - ptr) >= needed_space)
      return new_alloc(mmap, ptr, size);
  }
  return NULL;
}
