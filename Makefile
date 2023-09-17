SRCS = $(wildcard src/*.c)
OBJS = $(SRCS:.c=.o)
DEPS = $(SRCS:.c=.d)

CC = cc
CFLAGS = -Wall -Wextra -Werror -MMD -fPIC -pthread

HOSTNAME := $(shell hostname)

ifdef DEV
    CFLAGS += -g3
endif

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

LIBFT = libft/libft.a
NAME = libft_malloc_$(HOSTTYPE).so

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) -shared -o $(NAME) $(OBJS) $(LIBFT)
	ln -sf $(NAME) libft_malloc.so

clean:
	rm -f $(OBJS) $(DEPS)

fclean: clean
	rm -f $(NAME) libft_malloc.so

ffclean: fclean
	make -C libft fclean
	rm -f test

re: fclean all

rere: ffclean all

test: $(NAME)
	$(CC) $(CFLAGS) -O0 -o test test.c -L. -lft_malloc -Wl,-rpath=.

$(LIBFT):
	make -C libft

-include $(DEPS)

.PHONY: all clean fclean ffclean re rere test
