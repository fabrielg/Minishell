#include "exec.h"

int	cmd_echo(int argc, char **args, char ***env)
{
	printf("command : [echo]\n");
	(void)argc;
	(void)args;
	(void)env;
	return (SUCCESS);
}
