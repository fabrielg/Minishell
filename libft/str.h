/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabrielg <fabrielg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:56:09 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/08/18 16:25:16 by fabrielg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STR_H
# define STR_H

# include <stddef.h>

void	free_split(char **split);
char	**ft_split(char const *s, char c);
void	ft_strappend(char **s, char *to_append);
void	ft_strnappend(char **s, char *to_append, size_t size);
size_t	ft_strarrlen(char **str);
char	*ft_strchr(const char *s, int c);
char	*ft_strchrset(const char *s, char *set);
char	*ft_strdup(const char *s);
char	*ft_strndup(const char *s, size_t size);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlcat(char *dst, const char *src, size_t siz);
size_t	ft_strlcpy(char *dst, const char *src, size_t siz);
size_t	ft_strlen(const char *s);
size_t	ft_strlen_char(char const *str, char stop);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnotchr(const char *s, int c);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strnstr(const char *big, const char *little, size_t len);
long	ft_strtol(const char *str, char **endptr, int base);
char	*ft_strrchr(const char *s, int c);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	ft_upper(char *str);
void	ft_lower(char *str);

#endif
