#pragma once

#include "../libft/libft.h"
#include "pthread.h"
#include "stdio.h"
#include "stdlib.h"
#include "sys/mman.h"
#include "unistd.h"
#include <errno.h>
#include <fcntl.h>
#include <stdbool.h>
#include <string.h>

// logging implies big pefromance hit
#define LOGGING false
#define LOGFILE "/tmp/malloc.log"

#define MMAP_SHIFT(mmap) ((void *)mmap + sizeof(t_mmap))
#define ALLOC_SHIFT(alloc) ((void *)alloc + sizeof(t_alloc))

#define ALIGNMENT 16 // 8 on 32 bits, 16 on 64 bits
#define TINY_MMAP_SIZE (4 * getpagesize())
// 4*4096 - 100*(128+32) = 384 free space
#define TINY_ALLOC_SIZE (128)
#define SMALL_MMAP_SIZE (32 * getpagesize())
// 4*4096 - 100*(1024+32) = 25472 free space
#define SMALL_ALLOC_SIZE (1024)

typedef enum e_type { ANCHOR, TINY, SMALL, LARGE } t_type;

typedef struct s_alloc t_alloc; // declare it here to use it in s_mmap
typedef struct s_mmap {
  struct s_mmap *next;
  struct s_mmap *prev;
  t_type type;
  size_t size;
  t_alloc *alloc;
} t_mmap;

typedef struct s_alloc {
  struct s_alloc *next;
  struct s_alloc *prev;
  t_mmap *parent;
  size_t size;
} t_alloc;

extern t_mmap g_mmap;

// global_init.c
void lock_mutex();
void unlock_mutex();
int tmpfd();
void flog(char *title, size_t size);

// malloc.c
void *_malloc(size_t size);
void *malloc(size_t size);

// free.c
void _free(void *ptr);
void free(void *ptr);

// realloc.c
void *_realloc(void *ptr, size_t size);
void *realloc(void *ptr, size_t size);

// calloc.c
void *_calloc(size_t nmemb, size_t size);
void *calloc(size_t nmemb, size_t size);

// reallocarray.c
void *reallocarray(void *ptr, size_t nmemb, size_t size);

// alloc.c
t_alloc *find_alloc_ptr(void *ptr);
size_t get_alloc_size(size_t size);
t_alloc *find_alloc(size_t size);
t_alloc *new_alloc(t_mmap *mmap, void *ptr, size_t size);

// mmap.c
size_t get_mmap_size(size_t size);
t_type get_mmap_type(size_t size);
t_mmap *new_mmap(size_t size);

// show_alloc_mem.c
void show_alloc_mem();
void show_alloc_mem_asciidump();
void show_alloc_mem_hexdump();
char *get_type_string(t_type type);
