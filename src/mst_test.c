#include "minishell.h"

int	main(int argc, char *argv[], char **envp)
{
	(void)argc;
	(void)argv;
	t_mst	*mst;
	mst = mst_alloc_env(envp);
	t_mst	*node;

	node = mst_get_node(mst, "USER");
	mst_insertion(&mst, node);
	node = mst_get_node(mst, "USERR");
	mst_insertion(&mst, node);
	node = new_mst(new_dic("USERRR", "user test", false));
	mst_insertion(&mst, node);
	node = new_mst(new_dic("USERRR", "user test 2", false));
	mst_insertion(&mst, node);
	mst_deletion(&mst, "NONE");
	mst_deletion(&mst, "USERRR");
	mst_deletion(&mst, NULL);
	mst_deletion(&mst, "");
	mst_deletion(&mst, "USER");
	mst_deletion(&mst, "ZSH");
	node = new_mst(new_dic("USER", "reel user", false));
	mst_insertion(&mst, node);
	print_tree(mst);
	mst_clear(&mst);
	return (0);
}
