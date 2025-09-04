#include "lexer.h"
# include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>


//LEXING TESTS
int main(int argc, char *argv[])
{
	char	s[100] = "\'je suis un \'test";
	char *line;
	(void)argc;
	(void)argv;

	while (1)
	{
		line = readline("minichaise> ");

		if (!line)
			break;
		if (*line)
			add_history(line);
		lex_line(line);
		free(line);
	}
	return (0);
}
