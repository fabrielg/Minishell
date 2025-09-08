#include "exec.h"

int	cmd_exit(int argc, char **args, char ***env)
{
	printf("command : [exit]\n");
	(void)argc;
	(void)args;
	(void)env;
	return (SUCCESS);
}
