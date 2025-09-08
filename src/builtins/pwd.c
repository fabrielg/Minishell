#include "exec.h"

int	cmd_pwd(int argc, char **args, char ***env)
{
	printf("command : [pwd]\n");
	(void)argc;
	(void)args;
	(void)env;
	return (SUCCESS);
}
