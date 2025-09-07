# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fabrielg <fabrielg@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/15 22:24:21 by gfrancoi          #+#    #+#              #
#    Updated: 2025/08/17 23:00:42 by fabrielg         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY : all clean fclean re debug

NAME		= minishell
CUSTOM_NAME	= MiniChaise
CFLAGS		= -Wall -Wextra -Werror

LIBFT_DIR	= ./libft/
LIBFT		= $(LIBFT_DIR)libft.a

INCLUDES	= -I ./includes/ -I $(LIBFT_DIR)

MAIN_FILE	= token_tester

# All files in src/
FILES		=	env/bst_utils \
				env/env_display \
				env/env_free \
				env/env_node_init \
				env/env_node_utils \
				env/path_research \
				lexer/lexer_utils \
				lexer/lexer \
				lexer/smart_split_utils \
				lexer/smart_split \
				token/token_command_utils \
				token/token_constructor \
				token/token_logic_exp_utils \
				token/token_pipeline_utils \
				token/token_redir_utils \
				token/token_subshell_utils \
				token/token_word_utils

SRC_DIR		= ./src/
SRC_FILES	= $(addsuffix .c, $(FILES)) $(addsuffix .c, $(MAIN_FILE))
SRC			= $(addprefix $(SRC_DIR), $(SRC_FILES))

OBJ_DIR		= ./obj/
OBJ			= $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRC))

all : $(NAME)
	@echo "\e[1;92m$(CUSTOM_NAME) compiled successfully!\e[0m"

$(NAME) : $(LIBFT) $(OBJ_DIR) $(OBJ)
	cc $(CFLAGS) $(INCLUDES) $(OBJ) -L$(LIBFT_DIR) -lft -lreadline -lncurses -o $(NAME)

$(LIBFT) :
	make -C $(LIBFT_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(dir $@)
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

debug : CFLAGS += -DDEBUG_MODE=1
debug : all
