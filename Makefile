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
		path_utils.c \

OBJS := $(SRCS:.c=.o)

CC := cc
CFLAGS := -Wall -Wextra -Werror
RM := rm -f

.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME): $(OBJS) pipex.c
	$(CC) $(CFLAGS) -o $(NAME) pipex.c $(OBJS)

all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

t: all
	./pipex file1.txt "/usr/bin/sort" "/usr/bin/wc -l" file2.txt

.PHONY: all clean fclean re
