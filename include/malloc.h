#pragma once

#include "../libft/libft.h"
#include "pthread.h"
#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include <stdbool.h>

#define MMAP_SHIFT(start) (start + sizeof(t_mmap))
#define ALLOC_SHIFT(start) (start + sizeof(t_alloc))

#define TINY_MMAP_SIZE (4 * getpagesize())
#define SMALL_MMAP_SIZE (32 * getpagesize())
#define TINY_ALLOC_SIZE (128)
#define SMALL_ALLOC_SIZE (2048)

enum e_type { TINY, SMALL, LARGE };

typedef struct s_alloc t_alloc; // declare it here to use it in s_mmap
typedef struct s_mmap {
  struct s_mmap *next;
  struct s_mmap *prev;
  size_t remaining_alloc;
  t_alloc *alloc;
} t_mmap;

typedef struct s_alloc {
  struct s_alloc *next;
  struct s_alloc *prev;
  t_mmap *parent;
  bool is_used;
} t_alloc;

extern t_mmap *g_mmap;

// NOTE: mutex.c
void lock_mutex();
void unlock_mutex();

// malloc.c
void *_malloc(size_t size);
void *malloc(size_t size);
