/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-abr <alde-abr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 00:31:16 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/10/11 02:42:24 by alde-abr         ###   ########.fr       */
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
	REDIRECT_APPEND,
	REDIRECT_AMBIGUOUS
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
	char	**args;
	int		argc;
	t_list2	*redirects;
	int		pipes[2];
	int		pid;
}	t_command;

/* Structure representing a token */
struct s_token
{
	t_token_type	type;
	void			*data;
};

//[TOKEN-UTILS]_________________________________________

t_token			*token_new_op(const char *s, t_token_type type);
void			token_destroy(void *content);
t_token_type	detect_type(char *s);
void			token_display(t_token *token);
void			tokens_display(t_list2 *tokens);

//[TOKEN-WORD]_________________________________________

void			token_destroy_word(void *data);
bool			is_expandable_word(char *word);
void			token_display_word(char *word);

//[TOKEN-REDIRECT]_____________________________________

t_redirect		*parse_redir(char **contents, int *i);
t_token			*token_new_redir(char **contents, int *i);
void			token_destroy_redir(void *data);
void			token_display_redirect(t_redirect *redir);
t_redirect		*get_redir(void *data);

//[TOKEN-COMMAND]_______________________________________

t_command		*command_create(void);
t_token			*token_create_command(t_command *cmd);
void			token_display_command(t_command *cmd);
void			token_destroy_command(void *data);
t_command		*get_command(void *data);

#endif
