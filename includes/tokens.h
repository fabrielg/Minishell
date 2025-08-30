/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabrielg <fabrielg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 00:31:16 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/08/16 17:03:08 by fabrielg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
# define TOKENS_H

# include <stdbool.h>
# include "libft.h"
# include <stdlib.h>

typedef struct s_token	t_token;

/* Enumeration of different token types in the AST */
typedef enum e_token_type
{
	TOKEN_PIPELINE,
	TOKEN_LOGICAL_EXPRESSION,
	TOKEN_COMMAND,
	TOKEN_SUBSHELL,
	TOKEN_REDIRECT,
	TOKEN_WORD
}	t_token_type;

/* Types of logical operators (&& and ||) */
typedef enum e_logical_op
{
	LOGICAL_AND,
	LOGICAL_OR
}	t_logical_op;

/* Types of supported redirections (<, >, <<, >>) */
typedef enum e_redirect_type
{
	REDIRECT_INPUT,
	REDIRECT_OUTPUT,
	REDIRECT_HEREDOC,
	REDIRECT_APPEND
}	t_redirect_type;

/* Structure representing a word or argument */
typedef struct s_word
{
	char	*text;
	bool	quoted;
	bool	expandable;
}	t_word;

/* Structure for a redirection */
typedef struct s_redirect
{
	t_redirect_type	type;
	t_word			*file;
	int				fd;
}	t_redirect;

/* Structure for a simple command, args[0] is the command name */
typedef struct s_command
{
	char		**args;
	t_redirect	**redirects;
	int			arg_count;
	int			redirect_count;
}	t_command;

/* Structure for a subshell (commands between parentheses) */
typedef struct s_subshell
{
	t_token		*content;
	t_redirect	**redirects;
	int			redirect_count;
}	t_subshell;

/* Structure for a pipeline (commands connected by pipes |) */
typedef struct s_pipeline
{
	t_token	**commands;
	int		command_count;
}	t_pipeline;

/* Structure for logical expressions (&& and ||) */
typedef struct s_logical_expression
{
	t_logical_op	op;
	t_token			*left;
	t_token			*right;
}	t_logical_expression;

/* Union containing data specific to each token type */
typedef union u_token_data
{
	t_word					*word;
	t_command				*command;
	t_subshell				*subshell;
	t_pipeline				*pipeline;
	t_logical_expression	*logical_expr;
	t_redirect				*redirect;
}	t_token_data;

/* Structure representing a token */
struct s_token
{
	t_token_type	type;
	t_token_data	data;
};

t_token	*token_create(t_token_type type, void *content);
void	token_destroy(t_token *token);
void	token_clear(t_token **tokens, int token_count);

/* Functions utils for TOKEN_WORD */
t_token	*token_create_word(char *text, bool quoted, bool expandable);
void	token_destroy_word(t_word *word);

/* Functions utils for TOKEN_REDIRECT */
t_token	*token_create_redir(t_redirect_type type, t_word *file, int fd);
void	token_destroy_redir(t_redirect *redir);
void	token_clear_redir(t_redirect **redir, int rdc);

/* Functions utils for TOKEN_COMMAND */
t_token	*token_create_command(char **args, int ac, t_redirect **redir, int rdc);
void	token_destroy_command(t_command *command);
void	token_clear_commands(t_command **commands, int command_count);

/* Functions utils for TOKEN_SUBSHELL */
t_token	*token_create_subshell(t_token *content, t_redirect **redir, int rdc);
void	token_destroy_subshell(t_subshell *subshell);

/* Functions utils for TOKEN_PIPELINE */
t_token	*token_create_pipeline(t_token **commands, int command_count);
void	token_destroy_pipeline(t_pipeline *pipeline);

/* Functions utils for TOKEN_LOGICAL_EXPRESSION */
t_token	*token_create_logic_exp(t_logical_op op, t_token *left, t_token *right);
void	token_destroy_logic_exp(t_logical_expression *logic_exp);

#endif