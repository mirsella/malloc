#include "../include/malloc.h"

static pthread_mutex_t g_mutex = PTHREAD_MUTEX_INITIALIZER;

void lock_mutex() { pthread_mutex_lock(&g_mutex); }
void unlock_mutex() { pthread_mutex_unlock(&g_mutex); }
