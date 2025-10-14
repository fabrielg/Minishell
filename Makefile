# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alde-abr <alde-abr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/15 22:24:21 by gfrancoi          #+#    #+#              #
#    Updated: 2025/10/11 01:53:55 by alde-abr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY : all clean fclean re debug

NAME		= minishell
CUSTOM_NAME	= MiniChaise
CFLAGS		= -g3 -Wall -Wextra -Werror

LIBFT_DIR	= ./libft/
LIBFT		= $(LIBFT_DIR)libft.a

INCLUDES	= -I ./includes/ -I $(LIBFT_DIR)

CC = cc

MAIN_FILE	= main

# All files in src/
FILES		=	env/env_insert \
				env/env_display \
				env/env_free \
				env/env_node_init \
				env/env_node_utils \
				env/path_research \
				env/env_newtab \
				env/env_delete \
				env/env_get_min \
				env/env_debug \
				env/env_get_node \
				env/env_modif \
				exec/runtime/exec \
				exec/runtime/exec_command \
				exec/runtime/exec_pipeline_utils \
				exec/runtime/exec_pipeline \
				exec/runtime/exec_logical \
				exec/runtime/exec_subshell \
				exec/run_cmd \
				exec/run_one_builtin \
				exec/redirect_cmd \
				exec/run_utils \
				exec/builtin_utils \
				exec/shebang_utils \
				exec/pipes_utils \
				ast/ast_build \
				ast/ast_display \
				ast/ast_utils \
				ast/ast_build_pipeline \
				ast/ast_count_args_pipeline \
				builtins/cd \
				builtins/echo \
				builtins/env \
				builtins/exit \
				builtins/export \
				builtins/pwd \
				builtins/unset \
				signals/signals_handler \
				lexer/utils/lexer_utils \
				lexer/lexer \
				lexer/smart_split/flush \
				lexer/smart_split/smart_split_utils \
				lexer/smart_split/smart_split \
				lexer/smart_split/tokens_remove_quotes \
				parser/expander/expander_heredoc \
				parser/expander/expander_utils \
				parser/expander/expander \
				parser/group_commands/group_commands_utils \
				parser/group_commands/group_commands \
				parser/wildcard_manager/glob_args_commands \
				parser/wildcard_manager/glob_commands \
				parser/wildcard_manager/glob_dir \
				parser/wildcard_manager/glob_redirs_commands \
				parser/wildcard_manager/glob_token \
				parser/wildcard_manager/star_match \
				parser/utils/redir_getter \
				parser/parser \
				parser/tokenizer/tokenizer \
				parser/heredoc_manager/handle_heredoc \
				parser/heredoc_manager/create_heredoc \
				parser/heredoc_manager/heredoc_utils \
				token/token_command_utils \
				token/token_constructor \
				token/token_redir_utils \
				token/token_word_utils \
				minishell_utils/minishell_utils \
				minishell_utils/minishell_process \
				minishell_utils/print_error

SRC_DIR		= ./src/
SRC_FILES	= $(addsuffix .c, $(FILES)) $(addsuffix .c, $(MAIN_FILE))
SRC			= $(addprefix $(SRC_DIR), $(SRC_FILES))

OBJ_DIR		= ./obj/
OBJ			= $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRC))

all : $(NAME)
	@echo "\e[1;92m$(CUSTOM_NAME) compiled successfully!\e[0m"

$(NAME) : $(LIBFT) $(OBJ_DIR) $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJ) -L$(LIBFT_DIR) -lft -lreadline -o $(NAME)

$(LIBFT) :
	make -C $(LIBFT_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

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
