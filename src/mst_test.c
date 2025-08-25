#include "minishell.h"

int	main(int argc, char *argv[], char **envp)
{
	(void)argc;
	(void)argv;
	t_mst	*mst;
	mst = mst_alloc_env(envp);
	t_mst	*node;

	node = new_mst(split_env_var("USER=test"));
	mst_insertion(&mst, node);
	node = new_mst(split_env_var("TOTO=test"));
	mst_insertion(&mst, node);
	print_tree(mst);
	//mst_display(mst);
	mst_clear(&mst);
	return (0);
}
