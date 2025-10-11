#include "libft.h"
#include "tokens.h"
#include "wildcard.h"

/**
 * @brief Counts the total number of tokens after glob expansion.
 * @return Total number of expanded tokens.
 */
static int	count_expanded_tokens(char **args, int arg_count)
{
	int		total;
	int		i;
	int		n;
	char	**res;

	total = 0;
	i = 0;
	while (i < arg_count)
	{
		res = glob_token(args[i], &n);
		if (res)
			total += n;
		ft_free_map((void **)res, -1);
		i++;
	}
	return (total);
}

/**
 * @brief Copies an array of strings into a new argument array.
 */
static void	cpy_new_args(char **res, char **new_args, int *k, int n)
{
	int	i;

	i = -1;
	while (++i < n)
		new_args[(*k)++] = ft_strdup(res[i]);
}

/**
 * @brief Creates a new argument array with all glob expansions applied.
 * @return Pointer to the new argument array, or NULL on allocation failure.
 */
static char	**fill_expanded_tokens(char **args, int arg_count, int new_count)
{
	char	**new_args;
	int		i;
	int		k;
	int		n;
	char	**res;

	new_args = malloc(sizeof(char *) * (new_count + 1));
	if (!new_args)
		return (NULL);
	k = 0;
	i = 0;
	while (i < arg_count)
	{
		res = glob_token(args[i], &n);
		cpy_new_args(res, new_args, &k, n);
		ft_free_map((void **)res, -1);
		i++;
	}
	new_args[k] = NULL;
	return (new_args);
}

/**
 * @brief Expands all glob patterns in a command's arguments.
 */
void	glob_one_command(t_command *cmd)
{
	char	**old_args;
	char	**new_args;
	int		old_argc;
	int		new_argc;

	old_args = cmd->args;
	old_argc = cmd->argc;
	new_argc = count_expanded_tokens(old_args, old_argc);
	new_args = fill_expanded_tokens(old_args, old_argc, new_argc);
	if (!new_args)
		return ;
	ft_free_map((void **)old_args, -1);
	cmd->args = new_args;
	cmd->argc = new_argc;
}
