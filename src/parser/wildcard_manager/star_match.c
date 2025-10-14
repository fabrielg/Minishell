/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   star_match.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 21:22:01 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/10/14 21:22:01 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

/**
 * @brief Compare pattern and string character by character for '*'.
 * @return 1 if current matchup succeeds, 0 otherwise.
 */
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

/**
 * @brief Match a string against a pattern with '*' wildcards.
 * @return 1 if name matches pattern, 0 otherwise.
 */
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
