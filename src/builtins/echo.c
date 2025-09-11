#include "exec.h"

int	cmd_echo(t_list2 *args, t_mst **env)
{
	printf("command : [echo]\n");
	(void)args;
	(void)env;
	return (SUCCESS);
}
