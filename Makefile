NAME = pipex

BONUS_NAME = pipex_bonus

CC = cc
CFLAGS = -Werror -Wall -Wextra

RM = rm -f

LIBFT_PATH = ./libft
LIBFT = $(LIBFT_PATH)/libft.a

COMMON_SRCS = common_src/pipex_utils.c \
	      common_src/pipex_clean_up.c

SRCS = 	src/pipex.c

BONUS_SRCS = bonus_src/here_doc_handler.c \
	     bonus_scr/pipex_bonus.c

OBJS = $(SRCS:.c=.o)

COMMON_OBJS = $(COMMON_SRCS:.c=.o)

BONUS_OBJS = $(BONUS_SRCS: .c=.o)

all: $(LIBFT) $(NAME)

bonus: $(LIBFT) $(BONUS_NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_PATH)

$(NAME): $(COMMON_OBJS) $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT)

$(BONUS_NAME): $(COMMON_OBJS) $(BONUS_OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME_BONUS) $(LIBFT)

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS) $(COMMON_OBJS) $(BONUS_OBJS)
	$(MAKE) clean -C $(LIBFT_PATH)

fclean:
	$(RM) $(NAME) $(BONUS_NAME) $(COMMON_OBJS) $(BONUS_OBJS) $(OBJS)
	$(MAKE) fclean -C $(LIBFT_PATH)

re: fclean all

.PHONY: all clean fclean re bonus
