#include "../include/malloc.h"

char *get_type_string(t_type type) {
  if (type == TINY)
    return "TINY";
  if (type == SMALL)
    return "SMALL";
  return "LARGE";
}

void show_alloc_mem() {
  if (!g_mmap) {
    ft_putstr("No memory allocated\n");
    return;
  }
  size_t total = 0;
  for (t_mmap *mmap = g_mmap; mmap; mmap = mmap->next) {
    ft_printf("%s : %p\n", get_type_string(mmap->type), mmap);
    for (t_alloc *alloc = mmap->alloc; alloc; alloc = alloc->next) {
      ft_printf("%p - %p : %d bytes\n", ALLOC_SHIFT(alloc),
                ALLOC_SHIFT(alloc) + alloc->size, alloc->size);
      total += alloc->size;
    }
  }
  ft_printf("Total : %d bytes\n", total);
}
