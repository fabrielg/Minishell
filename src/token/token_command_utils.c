#include "tokens.h"

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

void	token_display_command(t_command *cmd)
{
    t_list2	*tmp;
	int		i;

    if (!cmd)
        return ;
    printf("=== TOKEN_COMMAND ===\n");
    printf("Arguments:\n");
	tmp = cmd->args;
    i = 0;
    while (tmp)
    {
        printf("  [%d] ", i++);
        token_display_word((t_word *)tmp->content);
        printf("\n");
        tmp = tmp->next;
    }
    printf("Redirections:\n");
    tmp = cmd->redirects;
    while (tmp)
    {
        token_display_redirect((t_redirect *)tmp->content);
        tmp = tmp->next;
    }
    printf("====================\n");
}

void	token_destroy_command(void *data)
{
	t_command	*command;

	command = (t_command *) data;
	if (!command)
		return ;
	ft_lstclear2(&command->args, token_destroy_word);
	ft_lstclear2(&command->redirects, token_destroy_redir);
	free(command);
}