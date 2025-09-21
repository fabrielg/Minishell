#include <stdlib.h>

static int	check_matchup(const char **p, const char **s, const char **star,
	const char **s_saved)
{
	if (**p == '*')
	{
		*star = (*p)++;
		*s_saved = *s;
	}
	else if (**p == **s)
	{
		(*p)++;
		(*s)++;
	}
	else if (*star)
	{
		*p = *star + 1;
		*s = ++(*s_saved);
	}
	else
		return (0);
	return (1);
}

int	star_match(const char *pat, const char *name)
{
	const char	*p = pat;
	const char	*s = name;
	const char	*star = NULL;
	const char	*s_saved = NULL;

	if (!pat || !name)
		return (0);
	if (name[0] == '.' && pat[0] != '.')
		return (0);
	while (*s)
	{
		if (!check_matchup(&p, &s, &star, &s_saved))
			return (0);
	}
	while (*p == '*')
		p++;
	return (*p == '\0');
}
