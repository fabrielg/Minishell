#include "libft.h"

char	*ft_strjoin3(char *s1, char *s2, char *s3)
{
	char	*new;
	int		i;
	int		j;

	if (!s1 || !s2 || !s3)
		return (NULL);
	i = 0;
	j = 0;
	new = malloc(ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3) + 1);
	if (!new)
		return (NULL);
	while (s1[i])
		new[j++] = s1[i++];
	i = 0;
	while (s2[i])
		new[j++] = s2[i++];
	i = 0;
	while (s3[i])
		new[j++] = s3[i++];
	new[j] = '\0';
	return (new);
}
