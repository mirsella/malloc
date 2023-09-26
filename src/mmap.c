#include "../include/malloc.h"

size_t get_mmap_size(size_t size) {
  if (size <= TINY_ALLOC_SIZE)
    return TINY_MMAP_SIZE + ALIGNMENT;
  if (size <= SMALL_ALLOC_SIZE)
    return SMALL_MMAP_SIZE + ALIGNMENT;
  return size + sizeof(t_alloc) + ALIGNMENT;
}

t_type get_mmap_type(size_t size) {
  if (size <= TINY_ALLOC_SIZE)
    return TINY;
  if (size <= SMALL_ALLOC_SIZE)
    return SMALL;
  return LARGE;
}

t_mmap *new_mmap(size_t size) {
  t_mmap *map =
      mmap(NULL, get_mmap_size(size) + sizeof(t_mmap), PROT_READ | PROT_WRITE,
           MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
  if (!map) {
    errno = ENOMEM;
    return NULL;
  }
  map->type = get_mmap_type(size);
  map->size = get_mmap_size(size);
  map->next = NULL;
  map->prev = NULL;
  map->alloc = NULL;
  if (!g_mmap)
    return g_mmap = map;
  for (t_mmap *tmp = g_mmap; tmp; tmp = tmp->next) {
    if (map < tmp) {
      map->prev = tmp->prev;
      map->next = tmp;
      tmp->prev = map;
      if (map->prev)
        map->prev->next = map;
      if (g_mmap == tmp)
        g_mmap = map;
      break;
    } else if (map > tmp && (map < tmp->next || !tmp->next)) {
      map->prev = tmp;
      map->next = tmp->next;
      tmp->next = map;
      if (map->next)
        map->next->prev = map;
      break;
    }
  }
  return map;
}
