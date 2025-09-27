#include "exec.h"
#include "minishell.h"
#include <sys/stat.h>
#include <errno.h>

#define BASH_DIR "/bin/bash"

t_uint8	no_shebang_case(char *arg, char **env_cpy, t_uint8 *exit_code)
{
	char	*tab[3];

	tab[0] = BASH_DIR;
	tab[1] = arg;
	tab[2] = NULL;
	execve(BASH_DIR, tab, env_cpy);
	free(env_cpy);
	if (errno == EACCES)
		return (cmd_err(exit_code, arg, NO_PERM_MSG, PERM_ERR));
	return (cmd_err(exit_code, arg, NOT_FOUND_MSG, NOT_FOUND_ERR));
}
