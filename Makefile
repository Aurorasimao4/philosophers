# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asimao <asimao@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/23 06:05:41 by asimao            #+#    #+#              #
#    Updated: 2024/10/23 06:22:32 by asimao           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
FLAGS = -Wall -Wextra -Werror
CC = cc
PROGRAM = # AQUI COLOCAR OS NOMES DAS PASTAS

OBJ = $(PROGRAM:.c=.o)

GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

all: $(NAME)
	@echo "$(GREEN)compilacao concluida :)!$(RESET)"

$(NAME) : $(OBJ)
				$(CC) $(FLAGS) $(OBJ) -o $(NAME)
				@echo "$(GREEN)Executavel gerado: $@$(RESET)"


clean:
				rm -f $(OBJ)
				@echo "$(RED)Arquivos objeto removidos.$(RESET)"
fclean: clean
				rm -f $(NAME)
				@echo "$(RED)Executável removido.$(RESET)"
re: fclean all
.PHONY: all clear 