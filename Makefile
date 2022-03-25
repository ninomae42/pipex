NAME := pipex
SRCS := ft_split.c \
		ft_stpcpy.c \
		ft_strchr.c \
		ft_strdup.c \
		ft_strjoin.c \
		ft_strlcpy.c \
		ft_strlen.c \
		ft_strncmp.c \
		ft_strnstr.c \
		ft_strrchr.c \
		ft_strtrim.c \
		ft_substr.c \
		ft_syscalls.c \
		open_utils.c \
		path_utils.c \
		pipe_utils.c \
		put_err.c \

OBJS := $(SRCS:.c=.o)

CC := cc
CFLAGS := -Wall -Wextra -Werror
RM := rm -f

.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME): $(OBJS) main.c
	$(CC) $(CFLAGS) -o $(NAME) main.c $(OBJS)

all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

t: all
	./pipex infile "sort" "cat" outfile

.PHONY: all clean fclean re
