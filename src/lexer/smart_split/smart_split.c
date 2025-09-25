#include "lexer.h"
#include <string.h>
#include "smart_split.h"

static void	handle_inside_quote(t_split_ctx *ctx, char c)
{
	if (c == ctx->quote)
		ctx->quote = 0;
}

static void	handle_outside_quote(t_split_ctx *ctx, char c, int *i)
{
	if (c == '\'' || c == '"')
	{
		if (ctx->start == -1)
			ctx->start = *i;
		ctx->quote = c;
	}
	else if (c == ' ' || c == '\t')
		flush_token(ctx, *i);
	else if (is_operator_char(c))
	{
		flush_token(ctx, *i);
		flush_operator(ctx, i);
	}
	else if (ctx->start == -1)
		ctx->start = *i;
}

static void	process_char(t_split_ctx *ctx, int *i)
{
	char	c;

	c = ctx->line[*i];
	if (ctx->quote)
		handle_inside_quote(ctx, c);
	else
		handle_outside_quote(ctx, c, i);
}

char	**smart_split(const char *line)
{
	t_split_ctx		ctx;
	int				i;

	ctx.line = line;
	ctx.capacity = 8;
	ctx.count = 0;
	ctx.start = -1;
	ctx.tokens = malloc(sizeof(char *) * ctx.capacity);
	ctx.quote = 0;
	ctx.can_flush = 0;
	if (!ctx.tokens)
		return (NULL);
	i = 0;
	while (line[i])
	{
		process_char(&ctx, &i);
		i++;
	}
	flush_token(&ctx, i);
	ctx.tokens[ctx.count] = NULL;
	tokens_remove_quotes(ctx);
	return (ctx.tokens);
}
