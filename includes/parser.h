/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabrielg <fabrielg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 23:23:16 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/09/08 23:23:16 by fabrielg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "libft.h"

/* Functions utils for parsing */
t_list2	*parser(char *command_line);
t_list2	*group_commands(t_list2 *tokens);
t_list2	*tokenize(char **contents);

#endif