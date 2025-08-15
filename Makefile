# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/15 22:24:21 by gfrancoi          #+#    #+#              #
#    Updated: 2025/08/15 23:54:41 by gfrancoi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY : all clean fclean re

NAME		= minishell
CUSTOM_NAME	= MiniChaise
CFLAGS		= -Wall -Wextra -Werror

LIBFT_DIR	= ./libft/
LIBFT		= $(LIBFT_DIR)libft.a

INCLUDES	= -I ./includes/

# All files in src/
FILES		= main

SRC_DIR		= ./src/
SRC_FILES	= $(addsuffix .c, $(FILES))
SRC			= $(addprefix $(SRC_DIR), $(SRC_FILES))

OBJ_DIR		= ./obj/
OBJ			= $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRC))

all : $(NAME)
	@echo "\e[1;92m$(CUSTOM_NAME) compiled successfully!\e[0m"

$(NAME) : $(LIBFT) $(OBJ_DIR) $(OBJ)
	cc $(CFLAGS) $(INCLUDES) $(OBJ) -L$(LIBFT_DIR) -lft -o $(NAME)

$(LIBFT) :
	make -C $(LIBFT_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	cc $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR) : 
	mkdir -p $(OBJ_DIR)

clean :
	rm -rf $(OBJ_DIR)
	make clean -C $(LIBFT_DIR)

fclean : clean
	rm -f $(NAME)
	make fclean -C $(LIBFT_DIR)

re : fclean all