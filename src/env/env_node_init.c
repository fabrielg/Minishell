#include "envp.h"

/**
 * @brief Creates a new dictionary entry with key-value pair.
 * @param key   Key string (stored by reference)
 * @param value Value string (stored by reference) 
 * @return New dictionary or NULL on malloc failure
 */
t_dic	*new_dic(char *key, char *value)
{
	t_dic	*dic;

	dic = (t_dic *) malloc(sizeof(t_dic));
	if (!dic)
		return (NULL);
	dic->key = key;
	dic->value = value;
	return (dic);
}

/**
 * @brief Creates a new MST node with given dictionary.
 * @param dic Dictionary to store in node (can be NULL)
 * @return New MST node or NULL on allocation failure
 */
t_mst	*new_mst(t_dic *dic)
{
	t_mst	*new;

	new = (t_mst *) ft_calloc(1, sizeof(t_mst));
	if (!new)
		return (NULL);
	new->dic = dic;
	return (new);
}

/**
 * @brief Creates MST from environment variables array.
 * @param env Array of environment strings (NULL terminated)
 * @return Root of MST containing all env vars or NULL
 */
t_mst	*mst_alloc_env(char **env)
{
	size_t	i;
	t_mst	*root;
	t_mst	*node;
	t_dic	*current_var;

	if (!env)
		return (NULL);
	root = NULL;
	i = 0;
	while (env[i])
	{
		current_var = split_env_var(env[i]);
		node = new_mst(current_var);
		mst_insertion(&root, node);
		i++;
	}
	return (root);
}
