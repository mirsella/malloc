#include "../include/malloc.h"

size_t get_alloc_size(size_t size) {
  if (size < TINY_ALLOC_SIZE)
    return TINY_ALLOC_SIZE + sizeof(t_alloc);
  if (size < SMALL_ALLOC_SIZE)
    return SMALL_ALLOC_SIZE + sizeof(t_alloc);
  return size + sizeof(t_alloc);
}

t_alloc *init_new_alloc(t_mmap *mmap, void *ptr, size_t size) {
  t_alloc *alloc = ptr;
  alloc->prev = alloc;
  alloc->next = alloc;
  alloc->size = size;
  alloc->parent = mmap;
  return alloc;
}

void *find_alloc(size_t size) {
  for (t_mmap *mmap = g_mmap; true; mmap = mmap->next) {
    if (!mmap) // really weird g_mmap should be allocated here
      return NULL;
    if (!mmap->alloc) // in case it's the first allocation of a mmap
      return mmap->alloc = init_new_alloc(mmap, MMAP_SHIFT(mmap), size);

    t_alloc *alloc = mmap->alloc;
    void *ptr = MMAP_SHIFT(mmap);
    while (alloc && ptr < (void *)MMAP_SHIFT(mmap) + mmap->size) {
      if (ptr < (void *)alloc) {
        if ((size_t)((void *)alloc - ptr) >= get_alloc_size(size)) {
          t_alloc *new = init_new_alloc(mmap, ptr, size);
          alloc->prev->next = new;
          new->prev = alloc->prev;
          new->next = alloc;
          alloc->prev = new;
        } else {
          ptr = ALLOC_SHIFT(alloc) + alloc->size;
        }
      } else {
        if (!alloc)
          break;
        alloc = alloc->next;
      }
    }
    if ((size_t)((void *)MMAP_SHIFT(mmap) + mmap->size - ptr) >=
        get_alloc_size(size)) {
      t_alloc *new = init_new_alloc(mmap, ptr, size);
      if (alloc) {
        alloc->prev->next = new;
        new->prev = alloc->prev;
        new->next = alloc;
        alloc->prev = new;
      } else {
        mmap->alloc = new;
      }
    }
    mmap = mmap->next;
  }
  return NULL;
}
