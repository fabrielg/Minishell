#include "tokens.h"
#include "libft.h"
#include <stdlib.h>

t_token	*token_create_word(char *text, bool quoted, bool expandable)
{
	t_token	*token;
	t_word	*word;

	token = (t_token *) malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	word = (t_word *) malloc(sizeof(t_word));
	if (!word)
		return (free(token), NULL);
	word->text = ft_strdup(text);
	if (!word->text)
		return (free(token), free(word), NULL);
	word->quoted = quoted;
	word->expandable = expandable;
	token->type = TOKEN_WORD;
	token->data.word = word;
	return (token);
}

t_token	*token_create_redir(t_redirect_type type, t_word *file, int fd)
{
	t_token		*token;
	t_redirect	*redir;

	token = (t_token *) malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	redir = (t_redirect *) malloc(sizeof(t_redirect));
	if (!redir)
		return (free(token), NULL);
	redir->type = type;
	redir->file = file;
	redir->fd = fd;
	token->type = TOKEN_REDIRECT;
	token->data.redirect = redir;
	return (token);
}

t_token	*token_create_command(char **args, int argc, t_redirect **redirects, int rdc)
{
	t_token		*token;
	t_command	*command;

	token = (t_token *) malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	command = (t_command *) malloc(sizeof(t_command));
	if (!command)
		return (free(token), NULL);
	command->args = args;
	command->arg_count = argc;
	command->redirects = redirects;
	command->redirect_count = rdc;
	token->type = TOKEN_COMMAND;
	token->data.command = command;
	return (token);
}

t_token	*token_create_subshell(t_token *content, t_redirect **redir, int rdc)
{
	t_token		*token;
	t_subshell	*subshell;

	token = (t_token *) malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	subshell = (t_subshell *) malloc(sizeof(t_subshell));
	if (!subshell)
		return (free(token), NULL);
	subshell->content = content;
	subshell->redirects = redir;
	subshell->redirect_count = rdc;
	token->type = TOKEN_SUBSHELL;
	token->data.subshell = subshell;
	return (token);
}

t_token	*token_create_pipeline(t_token **commands, int command_count)
{
	t_token		*token;
	t_pipeline	*pipeline;

	token = (t_token *) malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	pipeline = (t_pipeline *) malloc(sizeof(t_pipeline));
	if (!pipeline)
		return (free(token), NULL);
	pipeline->commands = commands;
	pipeline->command_count = command_count;
	token->type = TOKEN_PIPELINE;
	token->data.pipeline = pipeline;
	return (token);
}

t_token	*token_create_logical_exp(t_logical_op op, t_token *left, t_token *right)
{
	t_token					*token;
	t_logical_expression	*logical_exp;

	token = (t_token *) malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	logical_exp = (t_logical_expression *) malloc(sizeof(t_logical_expression));
	if (!logical_exp)
		return (free(token), NULL);
	logical_exp->op = op;
	logical_exp->left = left;
	logical_exp->right = right;
	token->type = TOKEN_LOGICAL_EXPRESSION;
	token->data.logical_expr = logical_exp;
	return (token);
}