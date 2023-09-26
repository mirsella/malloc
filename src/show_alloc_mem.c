#include "../include/malloc.h"
#include <unistd.h>

char *get_type_string(t_type type) {
  if (type == TINY)
    return "TINY";
  if (type == SMALL)
    return "SMALL";
  return "LARGE";
}

void show_alloc_mem() {
  lock_mutex();
  if (!g_mmap) {
    ft_putstr("show_alloc_mem(): No memory allocated\n");
    unlock_mutex();
    return;
  }
  size_t total = 0;
  for (t_mmap *mmap = g_mmap; mmap; mmap = mmap->next) {
    ft_printf("%s : %p\n", get_type_string(mmap->type), mmap);
    for (t_alloc *alloc = mmap->alloc; alloc; alloc = alloc->next) {
      if (!alloc)
        continue;
      ft_printf("%p - %p : %d bytes\n", ALLOC_SHIFT(alloc),
                ALLOC_SHIFT(alloc) + alloc->size, alloc->size);
      if (alloc->next == alloc) {
        ft_printf("detected infinite loop on alloc at %p\n",
                  ALLOC_SHIFT(alloc));
        break;
      }
      total += alloc->size;
    }
  }
  unlock_mutex();
  ft_printf("Total : %d bytes\n", total);
}

bool is_end(char *str, size_t size) {
  while (size--) {
    if (*str++ != 0)
      return false;
  }
  return true;
}
void asciidump(void *ptr, size_t size) {
  (void)ptr;
  size_t b;
  for (size_t i = 0; i < size; i++) {
    b = *((unsigned char *)ptr + i);
    if (ft_isprint(b))
      ft_printf("%c", b);
    else if (is_end(ptr + i + 1, size - i - 1)) {
      ft_printf("\\0");
      return;
    } else
      ft_printf(".");
  }
}
void hexdump(void *ptr, size_t size) {
  (void)ptr;
  size_t b;
  for (size_t i = 0; i < size; i++) {
    b = *((unsigned char *)ptr + i);
    ft_printf("0x%02x ", b);
    if (!b)
      return;
  }
}

void show_alloc_mem_asciidump() {
  lock_mutex();
  if (!g_mmap) {
    ft_putstr("show_alloc_mem_ex(): No memory allocated\n");
    unlock_mutex();
    return;
  }
  size_t total = 0;
  for (t_mmap *mmap = g_mmap; mmap; mmap = mmap->next) {
    ft_printf("%s : %p\n", get_type_string(mmap->type), mmap);
    for (t_alloc *alloc = mmap->alloc; alloc; alloc = alloc->next) {
      if (!alloc)
        continue;
      ft_printf("%p - %p : %d bytes\n", ALLOC_SHIFT(alloc),
                ALLOC_SHIFT(alloc) + alloc->size, alloc->size);
      asciidump(ALLOC_SHIFT(alloc), alloc->size);
      ft_putstr("\n\n");
      if (alloc->next == alloc) {
        ft_printf("detected infinite loop on alloc at %p\n",
                  ALLOC_SHIFT(alloc));
        break;
      }
      total += alloc->size;
    }
  }
  unlock_mutex();
  ft_printf("Total : %d bytes\n", total);
}

void show_alloc_mem_hexdump() {
  lock_mutex();
  if (!g_mmap) {
    ft_putstr("show_alloc_mem_ex(): No memory allocated\n");
    unlock_mutex();
    return;
  }
  size_t total = 0;
  for (t_mmap *mmap = g_mmap; mmap; mmap = mmap->next) {
    ft_printf("%s : %p\n", get_type_string(mmap->type), mmap);
    for (t_alloc *alloc = mmap->alloc; alloc; alloc = alloc->next) {
      if (!alloc)
        continue;
      ft_printf("%p - %p : %d bytes\n", ALLOC_SHIFT(alloc),
                ALLOC_SHIFT(alloc) + alloc->size, alloc->size);
      hexdump(ALLOC_SHIFT(alloc), alloc->size);
      ft_putstr("\n\n");
      if (alloc->next == alloc) {
        ft_printf("detected infinite loop on alloc at %p\n",
                  ALLOC_SHIFT(alloc));
        break;
      }
      total += alloc->size;
    }
  }
  unlock_mutex();
  ft_printf("Total : %d bytes\n", total);
}
