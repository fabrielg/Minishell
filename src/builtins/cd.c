/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 21:08:23 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/10/14 21:08:23 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/**
 * @brief Updates the PWD variable in the environment to current directory.
 * @return 0 on success, 1 on failure
 */
static int	assign_new_pwd(t_mst **env, t_mst *pwd)
{
	char	cwd[PATH_MAX_LEN];

	if (!pwd)
		return (0);
	if (!getcwd(cwd, PATH_MAX_LEN))
		return (1);
	return (mst_modif_value(env, "PWD", cwd));
}

/**
 * @brief Determines the target path for cd command.
 * @return Path string, or NULL if HOME not set
 */
static char	*get_cd_path(char *arg, t_mst *env)
{
	t_mst	*path;
	char	*ptr;

	if (!arg)
	{
		path = mst_get_node(env, "HOME");
		if (!path)
			return (write(2, "cd: HOME not set\n", 17), NULL);
		return (path->dic.value);
	}
	ptr = ft_strchr(arg, '$');
	if (ptr)
		ptr[0] = '\0';
	return (arg);
}

/**
 * @brief Executes the cd builtin, updating PWD and OLDPWD.
 * @return 0 on success, 1 on failure
 */
t_uint8	cmd_cd(char **args, t_mst **env)
{
	char		*path;
	t_mst		*pwd;
	char		*err_msg;
	t_uint8		err_code;

	path = get_cd_path(args[1], *env);
	if (!path)
		return (1);
	pwd = mst_get_node(*env, "PWD");
	if (pwd)
		if (mst_modif_value(env, "OLDPWD", pwd->dic.value))
			return (1);
	err_code = chdir(path);
	if (err_code)
	{
		err_msg = ft_strjoin("cd: ", path);
		perror(err_msg);
		free(err_msg);
		return (err_code);
	}
	if (assign_new_pwd(env, pwd))
		return (1);
	return (0);
}
