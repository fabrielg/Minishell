#include "exec.h"

int	cmd_unset(int argc, char **args, char ***env)
{
	printf("command : [unset]\n");
	(void)argc;
	(void)args;
	(void)env;
	return (SUCCESS);
}
