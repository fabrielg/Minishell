#include "tokens.h"

t_token	*token_create(t_token_type type, void *content)
{
	t_token_data	data;
	t_token			*token;

	data = (t_token_data) content;
	token = NULL;
	if (type == TOKEN_WORD)
		token = token_create_word(data.word->text, data.word->quoted,
				data.word->quoted);
	else if (type == TOKEN_REDIRECT)
		token = token_create_redir(data.redirect->type, data.redirect->file,
				data.redirect->fd);
	else if (type == TOKEN_COMMAND)
		token = token_create_command(data.command->args,
				data.command->arg_count, data.command->redirects,
				data.command->redirect_count);
	else if (type == TOKEN_SUBSHELL)
		token = token_create_subshell(data.subshell->content,
				data.subshell->redirects, data.subshell->redirect_count);
	else if (type == TOKEN_PIPELINE)
		token = token_create_pipeline(data.pipeline->commands,
				data.pipeline->command_count);
	else if (type == TOKEN_LOGICAL_EXPRESSION)
		token = token_create_logic_exp(data.logical_expr->op,
				data.logical_expr->left, data.logical_expr->right);
	return (token);
}

void	token_destroy(t_token *token)
{
	if (!token)
		return ;
	if (token->type == TOKEN_WORD)
		token_destroy_word(token->data.word);
	else if (token->type == TOKEN_REDIRECT)
		token_destroy_redir(token->data.redirect);
	else if (token->type == TOKEN_COMMAND)
		token_destroy_command(token->data.command);
	else if (token->type == TOKEN_SUBSHELL)
		token_destroy_subshell(token->data.subshell);
	else if (token->type == TOKEN_PIPELINE)
		token_destroy_pipeline(token->data.pipeline);
	else if (token->type == TOKEN_LOGICAL_EXPRESSION)
		token_destroy_logic_exp(token->data.logical_expr);
	else
		return ;
	free(token);
}
