NAME := pipex
SRC_DIR := ./srcs/
SRCS := exec.c \
		ft_syscall.c \
		get_path_envp.c \
		open_utils.c \
		pipe_utils.c \
		puterr.c \
		validate.c \

SRCS := $(addprefix $(SRC_DIR), $(SRCS))
OBJS := $(SRCS:.c=.o)
MAIN := main.c

CC := cc
CFLAGS := -Wall -Wextra -Werror
INCDIR := ./includes/
RM := rm -f

MAKE := make
LIBFT_DIR := ./libft/
INCDIR_LIBFT := ./libft/includes/
LIB := libft.a

.c.o:
	$(CC) $(CFLAGS) -I $(INCDIR) -I $(INCDIR_LIBFT) -c $< -o $(<:.c=.o)

$(NAME): $(LIB) $(OBJS) $(MAIN)
	$(CC) $(CFLAGS) -I $(INCDIR) -I $(INCDIR_LIBFT) $(LIB) -o $(NAME) $(OBJS) $(MAIN)

$(LIB): $(LIBFT_DIR)
	$(MAKE) -C ./libft/
	mv ./libft/libft.a .

all: $(NAME)

clean:
	$(MAKE) clean -C $(LIBFT_DIR)
	$(RM) $(OBJS)

fclean: clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	$(RM) $(LIB)
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
