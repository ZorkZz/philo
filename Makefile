# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: astachni <astachni@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/14 15:48:41 by astachni          #+#    #+#              #
#    Updated: 2023/06/27 17:42:23 by astachni         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS = srcs/init.c srcs/utils.c srcs/utils_chain_list.c srcs/death.c main.c

OBJS_DIR = objs/

OBJS = $(SRCS:%.c=$(OBJS_DIR)%.o)

CC = cc

CFLAGS = -Wall -Werror -Wextra -g3 #-fsanitize=address

RM = rm -rf

HEADER = header/philo.h

LIBS = -lpthread

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