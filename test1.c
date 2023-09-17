#include "include/malloc.h"
#include <string.h>

int main() {
  char *a = malloc(10);
  memcpy(a, "0123456789", 10);
  show_alloc_mem_asciidump();
  show_alloc_mem_hexdump();
}
