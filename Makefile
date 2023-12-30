# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: walidnaiji <walidnaiji@student.42.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/11 11:42:09 by wnaiji            #+#    #+#              #
#    Updated: 2023/12/30 15:12:25 by walidnaiji       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC =	main.c \
		outils.c \
		philo.c \
		outils_philo.c \

OBJ_DIR = obj
OBJS = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))

NAME = philo

CFLAGS = -Werror -Wextra -Wall -pthread #-fsanitize=thread -g3
SUCCESS_MSG = "\033[0;32mCompilation successful. $(NAME) created.\033[0m\n"
ERROR_MSG = "\033[0;31mCompilation failed.\033[0m\n"

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)
	@cc $(CFLAGS) -I . -c $< -o $@
	@printf "                  \rCompiling: $<"

$(NAME): $(OBJS)
	@cc $(CFLAGS) $(OBJS) -o $(NAME)
	@printf "\n"
	@printf $(SUCCESS_MSG)

all: $(NAME)

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
