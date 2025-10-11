#include "exec.h"

/**
 * @brief Checks if a string is a valid environment variable identifier.
 * @return 1 if valid, 0 otherwise
 */
static int	is_valid_identifier(char *arg)
{
	int	i;

	i = 1;
	if (!arg || !arg[0])
		return (0);
	if (!ft_isalpha(arg[0]) && arg[0] != '_')
		return (0);
	while (arg[i] && arg[i] != '=')
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

/**
 * @brief Prints an error message for an invalid export identifier.
 */
static void	print_export_err(char *arg)
{
	write(STDERR_FILENO, "export: `", 9);
	write(STDERR_FILENO, arg, ft_strlen(arg));
	write(STDERR_FILENO, "': not a valid identifier\n", 26);
}

/**
 * @brief Executes the export builtin, adding/updating environment variables.
 * @return 0 on success, EXIT_FAILURE on error
 */
t_uint8	cmd_export(char **args, t_mst **env)
{
	int				i;
	t_dic			dic;
	t_mst			*node;
	t_uint8			exit_code;

	i = 0;
	exit_code = 0;
	if (!args[1])
		return (bst_display(*env), exit_code);
	while (args[++i])
	{
		if (!is_valid_identifier(args[i]))
		{
			exit_code = 1;
			print_export_err(args[i]);
			continue ;
		}
		dic = split_env_var(args[i]);
		node = new_mst(dic);
		if (mst_insertion(env, node) == 1)
			return (1);
	}
	return (exit_code);
}
