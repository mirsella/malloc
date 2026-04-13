# malloc

Custom `malloc` implementation built as a shared library.

This project also includes a few extras: thread safety, logging, dump helpers, `calloc`, `reallocarray`, and a simple test program.

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

Reference tester:

- `https://gitlab.com/mmeisson_42/correction-tests/malloc`
