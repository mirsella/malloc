# malloc

Custom `malloc` implementation built as a shared library.

This project also includes thread safety, logging hooks, memory dump helpers, `calloc`, `reallocarray`, and a simple test program.

## How It Works

The allocator uses `mmap` to reserve memory regions and classifies allocations into tiny, small, and large buckets. Metadata for regions and allocations is tracked in linked lists, and the public allocator entry points are protected by a global mutex so the library can be used from multi-threaded programs.

The project also exposes debugging helpers such as `show_alloc_mem`, ASCII dumps, and hex dumps so it is easier to inspect how blocks are laid out.

## Build

```bash
make
```

## Quick test

```bash
make test
```

## Use with a program

```bash
LD_PRELOAD=./libft_malloc.so ls
```

## Notes

- The shared library name is host-specific and symlinked as `libft_malloc.so`.
- This is intended for Unix-like systems using `mmap`, `pthread`, and `LD_PRELOAD`.
- `make test` builds the demo test binary; you can run it afterward with `./test`.

Reference tester:

- `https://gitlab.com/mmeisson_42/correction-tests/malloc`
