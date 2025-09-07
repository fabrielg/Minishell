#include "tokens.h"

/*t_token	*token_create_command(char **args, int ac, t_redirect **redir, int rdc)
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
	command->arg_count = ac;
	command->redirects = redir;
	command->redirect_count = rdc;
	token->type = TOKEN_COMMAND;
	token->data.command = command;
	return (token);
}

void	token_clear_commands(t_command **commands, int command_count)
{
	int	i;

	if (!commands)
		return ;
	i = 0;
	while (i < command_count)
	{
		token_destroy_command(commands[i]);
		i++;
	}
	free(commands);
}

void	token_destroy_command(t_command *command)
{
	if (!command)
		return ;
	ft_free_map((void **) command->args, command->arg_count);
	token_clear_redir(command->redirects, command->redirect_count);
	free(command);
}*/