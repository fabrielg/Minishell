/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-abr <alde-abr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 21:07:21 by fabrielg          #+#    #+#             */
/*   Updated: 2025/09/15 00:19:06 by alde-abr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVP_H
# define ENVP_H

# include "minishell.h"

/* Structure for a dictionnary */
typedef struct s_dic
{
	char	*key;
	char	*value;
}	t_dic;

/* Structure for a multiple search tree (can be binary and linked) */
typedef struct s_mst	t_mst;
struct s_mst
{
	t_dic	dic;
	t_mst	*left;
	t_mst	*right;
	t_mst	*next;
};

/*[DISPLAY]___________________*/

void	mst_display(t_mst *mst);
void	bst_display(t_mst *tree);

/*[FREE]______________________*/

void	mst_free(t_mst **node);
void	mst_clear(t_mst **root);
void	freekey(t_dic *dic);

/*[INIT]______________________*/

t_dic	new_dic(char *key, char *value);
t_mst	*new_mst(t_dic dic);

/*[UTILS]______________________*/

t_mst	*mst_alloc_env(char **env);
t_mst	*mst_last(t_mst *root);
void	mst_add_back(t_mst **root, t_mst *new);
t_dic	split_env_var(char *env_var);

/*[BST UTILS]______________________*/

t_mst	*mst_get_parent(t_mst *tree, char *child);
t_mst	*mst_get_node(t_mst *tree, char *to_find);
int		mst_insertion(t_mst **tree, t_mst *node);

char	**env_newtab(t_mst *tree);
int		mst_delete(t_mst **tree, char	*key);
int		mst_size(t_mst *tree);

t_mst	*mst_get_min(t_mst *tree);
t_mst	*mst_get_min_parent(t_mst *tree);
t_mst	*mst_get_linked_min_parent(t_mst *tree);

int	debug_node(t_mst *node);

#endif
