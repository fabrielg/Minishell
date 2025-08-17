/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabrielg <fabrielg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 21:07:21 by fabrielg          #+#    #+#             */
/*   Updated: 2025/08/17 23:03:11 by fabrielg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include <stdlib.h>
# include <stdbool.h>

/* Structure for a dictionnary */
typedef struct s_dic
{
	char	*key;
	char	*value;
	bool	quoted;
}	t_dic;

/* Structure for a multiple search tree (can be binary and linked) */
typedef struct s_mst	t_mst;
struct s_mst
{
	t_dic	*dic;
	t_mst	*left;
	t_mst	*right;
	t_mst	*next;
};

t_dic	*new_dic(char *key, char *value);
t_mst	*new_mst(t_dic *dic);
t_mst	*mst_last(t_mst *root);
void	mst_add_back(t_mst **root, t_mst *new);
t_dic	*split_env_var(char *env_var);
t_mst	*mst_alloc_env(char **env);
void	mst_display(t_mst *mst);
void	mst_clear(t_mst **root);

#endif
