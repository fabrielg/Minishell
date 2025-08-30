#include "tokens.h"

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

void	token_destroy_pipeline(t_pipeline *pipeline)
{
	if (!pipeline)
		return ;
	token_clear(pipeline->commands, pipeline->command_count);
	free(pipeline);
}