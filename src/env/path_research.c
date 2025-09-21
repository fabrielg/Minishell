#include "minishell.h"

/**
 * Builds a full path by concatenating a directory and a command.
 * @param	cmd  Command name (e.g., "ls").
 * @param	path Env Directory path.
 * @return	New alloc string containing "path/cmd", or NULL memory fail.
 */
char	*create_path(char *cmd, char *path)
{
	char	*new;
	int		cmd_len;
	int		path_len;
	int		i;

	i = -1;
	cmd_len = ft_strlen(cmd);
	path_len = ft_strlen(path);
	new = malloc((cmd_len + path_len + 2) * sizeof(char));
	if (!new)
		return (NULL);
	while (++i < path_len)
		new[i] = path[i];
	new[i] = '/';
	while (++i < cmd_len + path_len + 1)
		new[i] = cmd[i - path_len - 1];
	new[i] = '\0';
	return (new);
}

/**
 * Searches for a command in directories in the PATH environment variable.
 * @param cmd		Command name to search for.
 * @param env_path	PATH environment variable string.
 * @return	Newly alloc string with the path to the cmd if found, else NULL.
 */
char	*research_path(char *cmd, char *env_path)
{
	char	*path;
	char	tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (env_path[i++])
	{
		if (env_path[i] != ':')
			continue ;
		tmp = env_path[i];
		env_path[i] = '\0';
		path = create_path(cmd, env_path + j);
		env_path[i] = tmp;
		if (!access(path, F_OK))
			return (path);
		free(path);
		j = i + 1;
	}
	return (NULL);
}
