#include "libft.h"
#include "wildcard.h"

/**
 * @brief Check if a token contains a wildcard '*'.
 * @return 1 if wildcard found, 0 otherwise.
 */
static int	has_wildcard(const char *token)
{
	return (!!ft_strchr(token, '*'));
}

/**
 * @brief Split a path into directory and pattern parts.
 */
static void	split_path(const char *token, char *dir, char *pattern)
{
	int	i;

	i = ft_strlen(token) - 1;
	while (i >= 0 && token[i] != '/')
		i--;
	if (i < 0)
	{
		ft_strcpy(dir, ".");
		ft_strcpy(pattern, token);
	}
	else if (i == 0)
	{
		ft_strcpy(dir, "/");
		ft_strcpy(pattern, token + 1);
	}
	else
	{
		ft_strlcpy(dir, token, i + 1);
		dir[i + 1] = 0;
		ft_strcpy(pattern, token + i + 1);
	}
}

/**
 * @brief Return a single token as an array.
 * @return Newly allocated array with the token.
 */
static char	**get_raw_token(const char *token, int *out_count)
{
	char	**res;

	res = malloc(sizeof(char *) * 2);
	if (!res)
		return (NULL);
	res[0] = ft_strdup(token);
	if (!res[0])
	{
		free(res);
		return (NULL);
	}
	res[1] = NULL;
	*out_count = 1;
	return (res);
}

/**
 * @brief Expand a token with wildcards using globbing.
 * @return Array of expanded tokens (malloc'ed).
 */
char	**glob_token(const char *token, int *out_count)
{
	char	dir[1024];
	char	pattern[256];
	char	**matches;

	*out_count = 0;
	if (!has_wildcard(token))
		return (get_raw_token(token, out_count));
	split_path(token, dir, pattern);
	matches = glob_dir(dir, pattern, out_count);
	if (!matches || *out_count == 0)
		return (get_raw_token(token, out_count));
	return (matches);
}
