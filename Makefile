# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wnaiji <wnaiji@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/11 11:42:09 by wnaiji            #+#    #+#              #
#    Updated: 2023/07/10 13:06:45 by wnaiji           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = main.c \
	parsing.c \
	outils_libft.c \
	philo.c \

OBJ_DIR = obj
OBJS = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))

NAME = philo

CFLAGS = -Werror -Wextra -Wall -pthread
SUCCESS_MSG = "\033[0;32mCompilation successful. $(NAME) created.\033[0m\n"
ERROR_MSG = "\033[0;31mCompilation failed.\033[0m\n"

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)
	@gcc $(CFLAGS) -I . -c $< -o $@
	@printf "                  \rCompiling: $<"

$(NAME): $(OBJS)
	@gcc $(CFLAGS) -L $(LIBFT_PATH) -l ft -L $(FT_PRINTF_PATH) -l ftprintf \
		-L $(GNL) -l get_next_line $(OBJS) -o $(NAME)
	@printf "\n"
	@printf $(SUCCESS_MSG)

all: $(NAME)

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
