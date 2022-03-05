# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/02 13:07:59 by ugdaniel          #+#    #+#              #
#    Updated: 2022/03/05 13:51:04 by ugdaniel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	philo

SRCS		=	srcs/main.c srcs/init.c srcs/libft.c srcs/philo.c srcs/log.c \
				srcs/eat.c srcs/check_death.c
OBJS		=	$(SRCS:.c=.o)
HEADERS		=	-I include

CC			=	clang
CFLAGS		=	-Wall -Werror -Wextra -pthread

# Colors
DEFAULT		=	\033[39m
GREEN		=	\033[92m
MAGENTA		=	\033[95m
YELLOW		=	\033[33m
GRAY		=	\033[37m
RED			=	\033[91m
CLEAR		=	\e[0m

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

.c.o:
	$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

norme:
	@python3 -m norminette

.PHONY: all clean fclean re
