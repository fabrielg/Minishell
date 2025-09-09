#include "minishell.h"

int	main(int argc, char *argv[], char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	t_list2	*tokens = parser("(cat    \"  input.txt\"&&echo    \"   'done  '  \")||grep   \"error\"   <log.txt>>   result.log|wc   -l");
	t_list2	*tmp = tokens;
	while (tmp)
	{
		t_token			*tok = (t_token *) tmp->content;
		t_token_type	type = tok->type;
		if (type == TOKEN_REDIRECT)
			token_display_redirect(tok->data);
		else if (type != TOKEN_COMMAND)
			token_display_word(tok->data);
		else
			token_display_command(tok->data);
		printf("\n");
		tmp = tmp->next;
	}
	ft_lstclear2(&tokens, token_destroy);
	return (0);
}
