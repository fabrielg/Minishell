#include "parser.h"

int main(void)
{
	int		n;
	char	**r;

	printf("Pattern: \"*.c\" in .\n");
	r = glob_token("*.c", &n);
	if (r)
	{
		printf("matches (%d):\n", n);
		for (int i = 0; i < n; i++)
		{
			printf("  %s\n", r[i]);
			free(r[i]);
		}
		free(r);
	} else
	{
		printf("no matches\n");
	}

	printf("\nPattern: \"*\" in .\n");
	r = glob_token("*", &n);
	if (r)
	{
		printf("matches (%d):\n", n);
		for (int i = 0; i < n; i++)
		{
			printf("  %s\n", r[i]);
			free(r[i]);
		}
		free(r);
	}
	else
		printf("no matches\n");

	printf("\nPattern: \".*\" in . (dotfiles)\n");
	r = glob_token(".*", &n);
	if (r)
	{
		printf("matches (%d):\n", n);
		for (int i = 0; i < n; i++)
		{
			printf("  %s\n", r[i]);
			free(r[i]);
		}
		free(r);
	}
	else
		printf("no matches\n");

	return (0);
}
