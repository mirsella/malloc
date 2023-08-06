#include "malloc.h"

pthread_mutex_t g_mutex = PTHREAD_MUTEX_INITIALIZER;
static t_mmap *g_mmap = NULL;
