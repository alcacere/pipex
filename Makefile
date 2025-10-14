# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alcacere <alcacere@student42madrid.co      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/10 02:01:31 by alcacere          #+#    #+#              #
#    Updated: 2025/10/10 02:03:42 by alcacere         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
NAME = pipex

BONUS_NAME = pipex_bonus

CC = cc
CFLAGS = -Werror -Wall -Wextra

RM = rm -f

LIBFT_PATH = ./libft
LIBFT = $(LIBFT_PATH)/libft.a

SRCS = src/pipex.c \
       src/pipex_clean_up.c \
       src/pipex_utils.c

BONUS_SRCS = bonus_src/here_doc_handler.c \
	     bonus_src/pipex_bonus.c \
	     bonus_src/pipex_clean_up_bonus.c \
	     bonus_src/pipex_utils_bonus.c

OBJS = $(SRCS:.c=.o)

BONUS_OBJS = $(BONUS_SRCS:.c=.o)

all: $(NAME)

bonus: $(BONUS_NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_PATH)

$(NAME): $(OBJS) $(COMMON_OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT)

$(BONUS_NAME): $(BONUS_OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(BONUS_NAME) $(BONUS_OBJS) $(LIBFT)

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS) $(BONUS_OBJS)
	$(MAKE) clean -C $(LIBFT_PATH)

fclean: clean
	$(RM) $(NAME) $(BONUS_NAME)
	$(MAKE) fclean -C $(LIBFT_PATH)

re: fclean all

.PHONY: all clean fclean re bonus
