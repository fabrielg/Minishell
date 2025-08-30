#include "minishell.h"

int	main(int argc, char *argv[], char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	t_list	*tokens;
	t_token	*token;
	char	*example_command_line = "echo '3 + 8' | bc > out";

	tokens = NULL;
	//token = token_create(TOKEN_COMMAND, );
	return (0);
}