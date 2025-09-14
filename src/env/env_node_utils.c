#include "envp.h"

/**
 * @brief Finds the last node in MST linked list.
 * @param root First node of the list
 * @return Last node or NULL if root is NULL
 */
t_mst	*mst_last(t_mst *root)
{
	t_mst	*node;

	node = root;
	if (node)
	{
		while (node->next)
			node = node->next;
	}
	return (node);
}

/**
 * @brief Adds new node at the end of MST list.
 * @param root Pointer to list head (modified if empty)
 * @param new  Node to add at the end
 */
void	mst_add_back(t_mst **root, t_mst *new)
{
	t_mst	*node;

	if (!root)
		return ;
	if (!(*root))
		*root = new;
	else
	{
		node = mst_last(*root);
		node->next = new;
	}
}

/**
 * @brief Splits environment variable into key-value dictionary.
 * @param env_var String in format "KEY=VALUE"
 * @return Dictionary with key/value or NULL on error
 */
t_dic	split_env_var(char *env_var)
{
	t_dic	dic;
	char	*copy;
	char	*key;
	char	*value;

	dic = new_dic(key, value);
	copy = ft_strdup(env_var);
	if (!copy)
		return (new_dic(NULL, NULL));
	value = ft_strchr(copy, '=');
	if (value)
	{
		value[0] = 0;
		value++;
	}
	key = copy;
	return (new_dic(key, value));
}
