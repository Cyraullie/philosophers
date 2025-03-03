# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/08 11:31:20 by cgoldens          #+#    #+#              #
#    Updated: 2025/03/03 14:46:03 by cgoldens         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo

CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -g
RM		= rm -rf

SRCDIR	= ./srcs/
OBJDIR	= ./objs/
INC		= ./include/

SRCS	= $(addprefix $(SRCDIR), main.c libft.c utils.c init.c philo.c eat.c print.c monitor.c)

OBJS	= $(SRCS:$(SRCDIR)%.c=$(OBJDIR)%.o)

GREEN	= \033[1;32m
CYAN	= \033[1;36m
YELLOW	= \033[1;33m
RESET	= \033[0m

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
	@echo "BY CGOLDENS"
	@echo "$(RESET)"

$(OBJDIR)%.o: $(SRCDIR)%.c
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -I $(INC) -o $(NAME)
	@echo "$(CYAN)Build completed!$(RESET)"

clean:
	@$(RM) $(OBJDIR)
	@echo "$(CYAN)Clean completed!$(RESET)"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(CYAN)Full clean completed!$(RESET)"

re: fclean all

norm:
	@norminette $(SRCDIR)*.c $(INC)*.h

.PHONY: all clean fclean re norm header
