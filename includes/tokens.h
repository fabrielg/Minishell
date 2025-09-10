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

/* Structure for a redirection */
typedef struct s_redirect
{
	t_redirect_type	type;
	char			*file;
	int				fd;
}	t_redirect;

/* Structure for a simple command, args[0] is the command name */
typedef struct s_command
{
	t_list2	*args;
	t_list2	*redirects;
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
	void			*data;
};

/* Functions utils for tokens */
t_token			*token_new_op(const char *s, t_token_type type);
void			token_destroy(void *content);
t_token_type	detect_type(char *s);

/* Functions utils for TOKEN_WORD */
//t_word			*parse_word(char *content);
t_token			*token_new_word(const char *s);
void			token_destroy_word(void *data);
void			token_display_word(char *word);
//t_word			*get_word(void *data);

/* Functions utils for TOKEN_REDIRECT */
t_redirect		*parse_redir(char **contents, int *i);
t_token			*token_new_redir(char **contents, int *i);
void			token_destroy_redir(void *data);
void			token_display_redirect(t_redirect *redir);
t_redirect		*get_redir(void *data);

/* Functions utils for TOKEN_COMMAND */
t_command		*command_create(void);
t_token			*token_create_command(t_command *cmd);
void			token_display_command(t_command *cmd);
void			token_destroy_command(void *data);
t_command		*get_command(void *data);

#endif