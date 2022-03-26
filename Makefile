NAME := pipex
SRCDIR := ./srcs/
SRCS := ft_syscalls.c \
		open_utils.c \
		path_utils.c \
		pipe_utils.c \
		put_err.c \

SRCS := $(addprefix $(SRCDIR), $(SRCS))
OBJS := $(SRCS:.c=.o)

MAIN := main.c

CC := cc
CFLAGS := -Wall -Wextra -Werror
MAKE := MAKE
INCDIR := ./includes/
INCDIR_LIBFT := ./libft/includes/
LIB := libft.a
RM := rm -f

.c.o:
	$(CC) $(CFLAGS) -I $(INCDIR) -I $(INCDIR_LIBFT) -c $< -o $(<:.c=.o)

$(NAME): $(LIB) $(OBJS) $(MAIN)
	$(CC) $(CFLAGS) -I $(INCDIR) -I $(INCDIR_LIBFT) $(LIB) -o $(NAME) $(OBJS) $(MAIN)

$(LIB):
	$(MAKE) -C ./libft
	cp ./libft/libft.a .

all: $(NAME)

clean:
	$(MAKE) clean -C ./libft
	$(RM) $(OBJS)

fclean: clean
	$(MAKE) fclean -C ./libft
	$(RM) $(LIB)
	$(RM) $(NAME)

re: fclean all

t: all
	./pipex infile "sort" "cat" outfile

.PHONY: all clean fclean re
