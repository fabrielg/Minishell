#include "envp.h"

/**
 * @brief Creates a new dictionary entry with key-value pair.
 * @param key   Key string (stored by reference)
 * @param value Value string (stored by reference) 
 * @return New dictionary or NULL on malloc failure
 */
t_dic	*new_dic(char *key, char *value, bool freeable)
{
	t_dic	*dic;

	dic = (t_dic *) malloc(sizeof(t_dic));
	if (!dic)
		return (NULL);
	dic->key = key;
	dic->value = value;
	dic->freeable = freeable;
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
