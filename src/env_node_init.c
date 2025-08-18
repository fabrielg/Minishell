#include "../includes/env.h"

/**
* @brief Sets quote type needed for shell value escaping.
* @param value String to analyze for special characters
* @param out   Output: 0=no quotes, 1=quotes, 2=special quotes
*/
static void	set_quoted(char *value, unsigned char *out)
{
	const char	*char_quoted = " !\"#$&()*-;<>=?[]\\^`{}|~";

	if (!value)
	{
		*out = 0;
		return ;
	}
	if (ft_strchr(value, '\''))
		*out = 2;
	else if (!value[0] || ft_strchrset(value, (char*)char_quoted))
		*out = 1;
	else
		*out = 0;
}

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
	set_quoted(dic->value, &dic->quoted);
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
