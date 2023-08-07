SRCS = $(wildcard src/*.c)
OBJS = $(SRCS:.c=.o)
DEPS = $(SRCS:.c=.d)

CC = cc
CFLAGS = -Wall -Wextra -Werror -MMD -fPIC -pthread

HOSTNAME := $(shell hostname)

ifneq (,$(filter $(HOSTNAME),laptop main)) # if HOSTNAME is laptop or main add -g3
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
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

ffclean: fclean
	make -C libft fclean

re: fclean all

rere: ffclean all

test: $(NAME)
	cc -o test test.c -L. -lft_malloc -Wl,-rpath=.

$(LIBFT):
	make -C libft

-include $(DEPS)

.PHONY: all clean fclean ffclean re rere test
