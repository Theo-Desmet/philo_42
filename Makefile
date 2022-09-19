# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tdesmet <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/14 08:53:24 by tdesmet           #+#    #+#              #
#    Updated: 2022/09/19 16:31:31 by tdesmet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -g3 -pthread -I includes/  #-fsanitize=thread #-Wall -Werror -Wextra

FILES = $(wildcard philo/*.c) $(wildcard philo/utils/*.c) main.c

OBJS = $(FILES:.c=.o)

NAME = philosopher

%.o: %.c
	@printf "\033[0;33mCompiling camarade: %-33.33s\r" $@
	@$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJS)
	@ $(CC) $(CFLAGS) -lpthread $(OBJS) -o  $(NAME) 

all: $(NAME)

clean:
	@ rm -f $(OBJS)
	@ printf '\033[0;32mclean done\033[0m\n'

fclean: clean
	@ rm -f $(NAME)
	@ printf '\033[0;32mfclean done\033[0m\n'

re: fclean all

.PHONY: all clean fclean re

.SILENT: $(OBJS)
