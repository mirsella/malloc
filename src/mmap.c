#include "../include/malloc.h"

size_t get_mmap_size(size_t size) {
  if (size < TINY_ALLOC_SIZE)
    return TINY_MMAP_SIZE;
  if (size < SMALL_ALLOC_SIZE)
    return SMALL_MMAP_SIZE;
  return size + sizeof(t_alloc);
}

t_type get_mmap_type(size_t size) {
  if (size < TINY_ALLOC_SIZE)
    return TINY;
  if (size < SMALL_ALLOC_SIZE)
    return SMALL;
  return LARGE;
}

t_mmap *new_mmap(size_t size) {
  t_mmap *map =
      mmap(NULL, get_mmap_size(size) + sizeof(t_mmap), PROT_READ | PROT_WRITE,
           MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
  if (!map)
    return NULL;
  map->type = get_mmap_type(size);
  map->size = get_mmap_size(size);
  map->next = NULL;
  map->prev = NULL;
  map->alloc = NULL;
  if (!g_mmap) {
    g_mmap = map;
    return map;
  }
  for (t_mmap *tmp = g_mmap; tmp; tmp = tmp->next) {
    if (map < tmp) {
      map->prev = tmp->prev;
      map->next = tmp;
      tmp->prev = map;
      if (map->prev)
        map->prev->next = map;
      if (g_mmap == tmp)
        g_mmap = map;
    } else if (map > tmp && (map < tmp->next || !tmp->next)) {
      map->prev = tmp;
      map->next = tmp->next;
      tmp->next = map;
      if (map->next)
        map->next->prev = map;
    }
  }
  return map;
}
