/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 21:25:25 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/10/14 21:25:25 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

# define SNG_QUOTED  0b0001
# define DBL_QUOTED  0b0010
# define WRD_READ    0b0100
# define RDR_READ    0b1000
# define IN_QUOTES   0b0011

# define STX_ERROR   2
# define STX_ERROR_MSG "syntax error near unexpected token `"

//[LEXER-UTILS]_________________________________________

int		check_operators(char *cmd_line, int *i, unsigned char	*byte);
int		check_parenthesis(char c, int *par_count, unsigned char byte);
void	toggle_quotes(char c, unsigned char *byte);
int		validate_stx(int par_count, unsigned char byte);

//[LEXER]_______________________________________________

int		lex_line(char *cmd_line);
int		print_stx_error(int err_code, char *err_msg, int size);

//[SMART-SPLIT-UTILS]____________________________________

char	*substr(const char *s, int start, int end);
int		is_operator_char(char c);
int		operator_len(const char *s, int i);

//[SMART_SPLIT]__________________________________________

char	**smart_split(const char *line);

#endif
