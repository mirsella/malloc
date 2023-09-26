#include <stdlib.h>

#define M (1024 * 1024)

int main()
{
    malloc(1);
    malloc(2);
    malloc(4);
    malloc(8);
    malloc(16);
    malloc(32);
    malloc(64);
    malloc(128);
    malloc(256);
    malloc(512);
    malloc(1024);
    malloc(1024 * 2);
    malloc(1024 * 4); 
    malloc(1024 * 32);
    malloc(M);
    malloc(16*M);
    malloc(128*M);
    show_alloc_mem(); 
    return (0); 
}
