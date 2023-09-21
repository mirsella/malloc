#include "../include/malloc.h"

void *_realloc(void *ptr, size_t size) {
  if (!ptr || !size)
    return NULL;
  /* t_alloc *alloc = ptr - sizeof(t_alloc); */
  t_alloc *alloc = find_alloc_ptr(ptr);
  if (!alloc) {
    if (LOGGING) {
      ft_dprintf(tmpfd(), "realloc(%p, %d): invalid pointer\n", ptr, size);
      /* flog("realloc: invalid pointer", (size_t)ptr); */
    }
    return NULL;
  }
  t_mmap *map = alloc->parent;

  // reduce space
  if (alloc->size >= size) {
    alloc->size = size;
    return ALLOC_SHIFT(alloc);
  }

  // find bigger space
  if (alloc->next && (size_t)alloc->next - (size_t)ptr >= size) {
    alloc->size = size;
    return ALLOC_SHIFT(alloc);
  } else if (!alloc->next &&
             (size_t)MMAP_SHIFT(map) + map->size - (size_t)ptr >= size) {
    alloc->size = size;
    return ALLOC_SHIFT(alloc);
  } else {
    void *new = _malloc(size);
    ft_memcpy(new, ALLOC_SHIFT(alloc), alloc->size);
    _free(ptr);
    return new;
  }
  return NULL;
}

void *realloc(void *ptr, size_t size) {
  if (LOGGING) {
    ft_dprintf(tmpfd(), "realloc(%p, %d)\n", ptr, size);
    /* flog("realloc(): ", size); */
  }
  while (size % ALIGNMENT != 0)
    size++;
  lock_mutex();
  void *res = NULL;
  if (!ptr)
    res = _malloc(size);
  else if (!size && ptr)
    _free(ptr);
  else
    res = _realloc(ptr, size);
  unlock_mutex();
  return res;
}
