# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/08 11:31:20 by cgoldens          #+#    #+#              #
#    Updated: 2024/12/16 14:46:57 by cgoldens         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
RM = rm -rf

SRCS = main.c libft.c utils.c init.c philo.c

OBJS = $(SRCS:.c=.o)

GREEN = \033[1;32m
CYAN = \033[1;36m
YELLOW = \033[1;33m
RESET = \033[0m

# Règles
all: header $(NAME)

header:
	@echo "$(GREEN)"
	@echo "    ____  __    _ __                       __                  "
	@echo "   / __ \/ /_  (_) /___  _________  ____  / /_  ___  __________"
	@echo "  / /_/ / __ \/ / / __ \/ ___/ __ \/ __ \/ __ \/ _ \/ ___/ ___/"
	@echo " / ____/ / / / / / /_/ (__  ) /_/ / /_/ / / / /  __/ /  (__  ) "
	@echo "/_/   /_/ /_/_/_/\____/____/\____/ .___/_/ /_/\___/_/  /____/  "
	@echo "                                /_/                            "
	@echo "$(RESET)"


%.o: %.c
	@$(CC) $(CFLAGS) -I ./ -c -o $@ $<

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(CYAN)Build completed!$(RESET)"

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)


re: fclean all

.PHONY: all clean fclean re
