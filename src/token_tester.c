#include "minishell.h"

int	main(int argc, char *argv[], char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	//char	*example_command_line = "echo '3 + 8' | bc > out";
	//char	*example_command_line2 = "echo '3 + 8' > out";
	t_token_data	cmd_data = token_parse_word("echo '3 + 8'");
	t_token			*token = token_create(TOKEN_WORD, &cmd_data);
	if (token)
		printf("token cmd = [%s]\n", token->data.word->text);
	else
		return (1);	
	token_destroy(token);
	
	t_token_data	redir_data = token_parse_redir(" <<   'out'");
	token = token_create(TOKEN_REDIRECT, &redir_data);
	if (token)
		printf("token redir = [%s] type: %d\n", token->data.redirect->file->text, token->data.redirect->type);
	else
		return (1);	
	token_destroy(token);
	return (0);
}