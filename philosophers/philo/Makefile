# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aoutumur <aoutumur@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/14 10:58:17 by aoutumur          #+#    #+#              #
#    Updated: 2025/05/08 10:53:15 by aoutumur         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =		philo

SRCS =		srcs/main.c \
			srcs/parsing.c \
			srcs/time.c \
			srcs/philosopher.c \
			srcs/init.c \
			srcs/output.c \
			srcs/exit_error_handling.c\
			srcs/monitor.c \

OBJS =		$(SRCS:.c=.o)
INCLUDES =	-I./includes

CC		=	gcc
CFLAGS	=	-Werror -Wall -Wextra -pthread

all:		$(NAME)
$(NAME):	$(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
clean:
	rm -f $(OBJS)
fclean: clean
	rm -f $(NAME)
re: fclean all
.PHONY: all clean fclean re
