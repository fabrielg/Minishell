#include "minishell.h"

static char	*get_tokentype_name(t_token_type type)
{
	if (type == TOKEN_WORD)
		return "TOKEN_WORD";
	else if (type == TOKEN_REDIRECT)
		return "TOKEN_REDIRECT";
	else if (type == TOKEN_COMMAND)
		return "TOKEN_COMMAND";
	else if (type == TOKEN_SUBSHELL)
		return "TOKEN_SUBSHELL";
	else if (type == TOKEN_PIPELINE)
		return "TOKEN_PIPELINE";
	else if (type == TOKEN_LOGICAL_EXPRESSION)
		return "TOKEN_LOGICAL_EXPRESSION";
	return (NULL);
}

int	main(int argc, char *argv[], char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	/*//char	*example_command_line = "echo '3 + 8' | bc > out";
	//char	*example_command_line2 = "echo '3 + 8' > out";
	t_token_data	cmd_data = token_parse_word("echo '3 + 8'");
	t_token			*token = token_create(TOKEN_WORD, &cmd_data);
	t_list			*tokens = NULL;
	if (token)
		printf("token cmd = [%s]\n", token->data.word->text);
	else
		return (1);
	ft_lstadd_back(&tokens, ft_lstnew(token));
	// token_destroy(token);
	
	t_token_data	redir_data = token_parse_redir(" <<   'out'");
	token = token_create(TOKEN_REDIRECT, &redir_data);
	if (token)
		printf("token redir = [%s] type: %d\n", token->data.redirect->file->text, token->data.redirect->type);
	else
		return (1);
	ft_lstadd_back(&tokens, ft_lstnew(token));
	ft_lstclear(&tokens, token_destroy);
	// token_destroy(token);*/
	char	**contents = smart_split("(cat    \"  input.txt\"&&echo    \"   'done  '  \")||grep   \"error\"   <log.txt>>   result.log|wc   -l");
	if (!contents)
		return (0);
	for (int i = 0; contents[i]; i++)
		printf("content %i = [%s]\n", i, contents[i]);
	t_list2	*tokens;

	tokens = parse_contents(contents);
	t_list2	*tmp = tokens;
	while (tmp)
	{
		t_token			*tok = (t_token *) tmp->content;
		t_token_type	type = tok->type;
		printf("type:	%s\n", get_tokentype_name(type));
		if (type == TOKEN_WORD)
			printf("text:[%s] \t\tquoted:[%d]\t\texpandlable:[%d]\n", ((t_word *)(tok->data))->text, ((t_word *)(tok->data))->quoted, ((t_word *)(tok->data))->expandable);
		else if (type == TOKEN_REDIRECT)
			printf("type:[%d]\t\tfile:[%s]\t\tfd:[%d]\n", ((t_redirect *)(tok->data))->type, ((t_redirect *)(tok->data))->file->text, ((t_redirect *)(tok->data))->fd);
		printf("\n");
		tmp = tmp->next;
	}
	ft_lstclear2(&tokens, token_destroy);
	ft_free_map((void **) contents, -1);
	return (0);
}