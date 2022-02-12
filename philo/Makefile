# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/02 13:07:59 by ugdaniel          #+#    #+#              #
#    Updated: 2022/02/12 15:24:50 by ugdaniel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	philo

SRCS		=	$(wildcard srcs/*.c srcs/*/*.c srcs/*/*/*.c srcs/*/*/*/*.c)
OBJS		=	$(SRCS:.c=.o)
HEADERS		=	-I include \

CC			=	@clang
CFLAGS		=	-Wall -Werror -Wextra -pthread

# Colors
DEFAULT		=	\033[39m
GREEN		=	\033[92m
MAGENTA		=	\033[95m
YELLOW		=	\033[33m
GRAY		=	\033[37m
RED			=	\033[91m
CLEAR		=	\e[0m

#wildca:
#	@echo "$(foreach src,$(SRCS),$(src)\n)"

all: $(NAME)
	@printf "\033[2K\r$(GREEN)$(NAME) ready!\n$(DEFAULT)"

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

.c.o:
	@printf "\033[2K\r$(YELLOW)Compiling $< $(_DEFAULT)"
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

clean:
	@printf "$(MAGENTA)Removed object files $(_DEFAULT)\n"
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME)
	@printf "$(RED)Removed $(NAME)$(_DEFAULT)\n"

re: fclean newline all

newline:
	@printf "$(_DEFAULT)\n"

.PHONY: all clean fclean re newline
