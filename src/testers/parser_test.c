#include "minishell.h"

int	main(int argc, char *argv[], char **envp)
{
	//t_list2	*tokens = parser("(cat    \"  input.txt\"&&echo    \"   'done  '  \")||grep   \"error\"   <'  $TOTO log.txt '>>   \"$TOTO result.log\"|wc   -l");
	if (argc != 2)
		return (0);
	t_mst	*env = mst_alloc_env(envp);
	t_list2	*tokens = parser(argv[1]);
	expander(tokens, env, 127);
	tokens_display(tokens);
	ft_lstclear2(&tokens, token_destroy);
	mst_clear(&env);
	return (0);
}
