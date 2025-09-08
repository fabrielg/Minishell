/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-abr <alde-abr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 00:31:16 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/09/08 16:35:52 by alde-abr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
# define TOKENS_H

# include <stdbool.h>

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

#endif
