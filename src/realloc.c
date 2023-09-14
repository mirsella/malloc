#include "../include/malloc.h"

void *_realloc(void *ptr, size_t size) {
  if (!ptr || !size)
    return NULL;
  t_alloc *alloc = ptr - sizeof(t_alloc);
  t_mmap *map = alloc->parent;

  // reduce space
  if (alloc->size >= size) {
    alloc->size = size;
    return ptr;
  }

  // find bigger space
  if (alloc->next && (size_t)alloc->next - (size_t)ptr >= size) {
    alloc->size = size;
    return ptr;
  } else if (!alloc->next &&
             (size_t)MMAP_SHIFT(map) + map->size - (size_t)ptr >= size) {
    alloc->size = size;
    return ptr;
  } else {
    void *new = _malloc(size);
    ft_memcpy(new, ALLOC_SHIFT(alloc), alloc->size);
    _free(ptr);
    return new;
  }
  return NULL;
}

void *realloc(void *ptr, size_t size) {
  ft_printf("realloc(%d) on %p", size, ptr);
  lock_mutex();
  // TODO: rsyslog()
  void *res = NULL;
  if (!ptr)
    res = _malloc(size);
  else if (!size && ptr) {
    _free(ptr);
    res = NULL;
  } else
    res = _realloc(ptr, size);
  unlock_mutex();
  ft_printf(" -> %p\n", res);
  return res;
}
