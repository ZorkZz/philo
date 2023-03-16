# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: astachni <astachni@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/14 15:48:41 by astachni          #+#    #+#              #
#    Updated: 2023/03/16 15:28:41 by astachni         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS = srcs/init.c srcs/utils.c main.c

OBJS_DIR = objs/

OBJS = $(SRCS:%.c=$(OBJS_DIR)%.o)

CC = cc

CFLAGS = -Wall -Werror -Wextra

RM = rm -rf

HEADER = header/philo.h

all: $(NAME)

$(OBJS_DIR)%.o: %.c $(HEADERS) Makefile
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME):	$(OBJS) $(LIBS) $(HEADERS) Makefile
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)
	@norminette

clean:
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all

.PHONY: all clean fclean re