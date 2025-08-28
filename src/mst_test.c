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
	node = new_mst(split_env_var("TOTO=test2"));
	mst_insertion(&mst, node);
	// mst_deletion(&mst, "NOTHING");
	// mst_deletion(&mst, "TOTO");
	mst_deletion(&mst, "USER");
	print_tree(mst);
	printf("\n\n\n");
	mst_display(mst);
	mst_clear(&mst);
	printf("fin\n\n");
	return (0);
}
