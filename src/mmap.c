#include "../include/malloc.h"

size_t get_mmap_size(size_t size) {
  if (size < TINY_ALLOC_SIZE)
    return TINY_MMAP_SIZE + sizeof(t_mmap);
  if (size < SMALL_ALLOC_SIZE)
    return SMALL_MMAP_SIZE + sizeof(t_mmap);
  return size + sizeof(t_mmap);
}

t_type get_mmap_type(size_t size) {
  if (size < TINY_ALLOC_SIZE)
    return TINY;
  if (size < SMALL_ALLOC_SIZE)
    return SMALL;
  return LARGE;
}
