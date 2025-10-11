/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-abr <alde-abr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 00:31:16 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/10/11 02:39:52 by alde-abr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WILDCARD_H
# define WILDCARD_H

# include "tokens.h"

//[WILDCARDS]_________________________________________

int		glob_redirects_list(t_list2 *redirects);
void	glob_one_command(t_command *cmd);
char	**glob_token(const char *token, int *out_count);
char	**glob_dir(const char *dir, const char *pattern, int *out_count);
int		star_match(const char *pat, const char *name);

#endif
