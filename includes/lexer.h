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

//lexer_utils____________________

int		check_operators(char *cmd_line, int *i, unsigned char	*byte);
int		check_parenthesis(char c, int *par_count, unsigned char byte);
void	toggle_quotes(char c, unsigned char *byte);
int		validate_stx(int par_count, unsigned char byte);

//lexer__________________________

int		lex_line(char *cmd_line);
int		print_stx_error(int err_code, char *err_msg, int size);

//smart_split_utils______________

char	*substr(const char *s, int start, int end);
int		is_operator_char(char c);
int		operator_len(const char *s, int i);

//smart_split____________________

char	**smart_split(const char *line);

#endif
