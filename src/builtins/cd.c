#include "exec.h"

int	cmd_cd(int argc, char **args, char ***env)
{
	printf("command : [cd]\n");
	(void)argc;
	(void)args;
	(void)env;
	return (SUCCESS);
}
