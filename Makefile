NAME = pipex

CC = cc
CFLAGS = -Werror -Wall -Wextra

RM = rm -f

LIBFT_PATH = ./libft
LIBFT = $(LIBFT_PATH)/libft.a

SRCS = 	src/pipex.c \
		src/pipex_utils.c \
		src/pipex_clean_up.c

OBJS = $(SRCS:.c=.o)

all: $(LIBFT) $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_PATH)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT)

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)
	$(MAKE) clean -C $(LIBFT_PATH)

fclean: clean
	$(RM) $(NAME)
	$(MAKE) fclean -C $(LIBFT_PATH)

re: fclean all

.PHONY: all clean fclean re
