#include "tokens.h"

/**
 * @brief Create a TOKEN_COMMAND token from a command structure.
 * @return Pointer to the new token or NULL on allocation failure.
 */
t_token	*token_create_command(t_command *cmd)
{
	t_token		*token;

	token = (t_token *) malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = TOKEN_COMMAND;
	token->data = cmd;
	return (token);
}

/**
 * @brief Allocate and initialize a new command structure.
 * @return Pointer to the new command or NULL on allocation failure.
 */
t_command	*command_create(void)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->redirects = NULL;
	return (cmd);
}

/**
 * @brief Display the details of a command (arguments, redirects, pipes).
 */
void	token_display_command(t_command *cmd)
{
	t_list2	*tmp;
	int		i;

	if (!cmd)
		return ;
	printf("=== TOKEN_COMMAND ===\n");
	printf("Arguments:\n");
	i = 0;
	while (i < cmd->argc)
	{
		printf("  [%d] ", i);
		token_display_word(cmd->args[i]);
		printf("\n");
		i++;
	}
	printf("Redirections:\n");
	tmp = cmd->redirects;
	while (tmp)
	{
		token_display_redirect((t_redirect *)tmp->content);
		tmp = tmp->next;
	}
	printf("pipes[0] = %d\npipes[1] = %d\n", cmd->pipes[0], cmd->pipes[1]);
	printf("====================\n");
}

/**
 * @brief Free a command structure and its contents.
 */
void	token_destroy_command(void *data)
{
	t_command	*command;

	command = (t_command *) data;
	if (!command)
		return ;
	ft_free_map((void *) command->args, command->argc);
	ft_lstclear2(&command->redirects, token_destroy_redir);
	free(command);
}

/**
 * @brief Retrieve the command from token data.
 * @return Pointer to the command.
 */
t_command	*get_command(void *data)
{
	t_command	*cmd;

	cmd = (t_command *) data;
	return (cmd);
}
