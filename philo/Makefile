# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: astachni <astachni@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/14 15:48:41 by astachni          #+#    #+#              #
#    Updated: 2023/06/30 15:11:03 by astachni         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS = srcs/init.c srcs/utils.c srcs/utils_chain_list.c srcs/death.c srcs/actions.c main.c srcs/free_functions.c srcs/parsing.c

OBJS_DIR = objs/

OBJS = $(SRCS:%.c=$(OBJS_DIR)%.o)

CC = cc

CFLAGS = -Wall -Werror -Wextra -g3 -fsanitize=thread

RM = rm -rf

HEADER = header/philo.h

LIBS = -lpthread

all: $(NAME)

$(OBJS_DIR)%.o: %.c $(HEADER) Makefile
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME):	$(OBJS) $(LIBS) $(HEADER) Makefile
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)
	@norminette

clean:
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all

.PHONY: all clean fclean re