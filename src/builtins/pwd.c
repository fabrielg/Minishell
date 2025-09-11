#include "exec.h"

int	cmd_pwd(t_list2 *args, t_mst **env)
{
	printf("command : [pwd]\n");
	(void)args;
	(void)env;
	return (SUCCESS);
}
