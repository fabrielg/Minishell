#include "exec.h"

int	cmd_exit(t_list2 *args, t_mst **env)
{
	printf("command : [exit]\n");
	(void)args;
	(void)env;
	return (SUCCESS);
}
