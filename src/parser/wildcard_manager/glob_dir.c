#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include "libft.h"
#include "wildcard.h"

static int	count_matches(const char *dir, const char *pattern)
{
	DIR				*d;
	struct dirent	*entry;
	int				count;
	const char		*name;

	count = 0;
	d = opendir(dir);
	if (!d)
		return (0);
	entry = readdir(d);
	while (entry)
	{
		name = entry->d_name;
		if (ft_strcmp(name, ".") == 0 || ft_strcmp(name, "..") == 0)
		{
			entry = readdir(d);
			continue ;
		}
		if (star_match(pattern, name))
			count++;
		entry = readdir(d);
	}
	closedir(d);
	return (count);
}

static void	bubble_sort(char **arr, int n)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (i < n - 1)
	{
		j = 0;
		while (j < n - i - 1)
		{
			if (ft_strcmp(arr[j], arr[j + 1]) > 0)
			{
				tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

static void	fill_matches(const char *dir, const char *pattern, char **res)
{
	DIR				*d;
	struct dirent	*entry;
	int				i;
	const char		*name;

	d = opendir(dir);
	entry = readdir(d);
	i = 0;
	while (entry)
	{
		name = entry->d_name;
		if (ft_strcmp(name, ".") == 0 || ft_strcmp(name, "..") == 0)
		{
			entry = readdir(d);
			continue ;
		}
		if (star_match(pattern, name))
			res[i++] = ft_strdup(name);
		entry = readdir(d);
	}
	res[i] = NULL;
	closedir(d);
}

char	**glob_dir(const char *dir, const char *pattern, int *out_count)
{
	int		count;
	char	**res;

	count = count_matches(dir, pattern);
	*out_count = count;
	if (count == 0)
		return (NULL);
	res = malloc(sizeof(char *) * (count + 1));
	if (!res)
		return (NULL);
	fill_matches(dir, pattern, res);
	bubble_sort(res, count);
	return (res);
}
