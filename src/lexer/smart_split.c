#include "lexer.h"
#include <string.h>

typedef struct s_split_ctx
{
	const char	*line;
	char		**tokens;
	int			capacity;
	int			count;
	int			start;
}	t_split_ctx;

static int	ensure_capacity(t_split_ctx *ctx)
{
	if (ctx->count < ctx->capacity - 1)
		return (1);
	ctx->capacity *= 2;
	ctx->tokens = realloc(ctx->tokens, sizeof(char *) * ctx->capacity);
	return (ctx->tokens != NULL);
}

static void	flush_token(t_split_ctx *ctx, int end)
{
	if (ctx->start == -1)
		return ;
	ctx->tokens[ctx->count++] = substr(ctx->line, ctx->start, end);
	ctx->start = -1;
	ensure_capacity(ctx);
}

static void	flush_operator(t_split_ctx *ctx, int *i)
{
	int	oplen;

	oplen = operator_len(ctx->line, *i);
	ctx->tokens[ctx->count++] = substr(ctx->line, *i, *i + oplen);
	ensure_capacity(ctx);
	*i += oplen - 1;
}

static void	process_char(t_split_ctx *ctx, unsigned char *state, int *i)
{
	char	c;
	
	c = ctx->line[*i];
	toggle_quotes(c, state);
	if (!(*state & IN_QUOTES))
	{
		if (c == ' ' || c == '\t')
			flush_token(ctx, *i);
		else if (is_operator_char(c))
		{
			flush_token(ctx, *i);
			flush_operator(ctx, i);
		}
		else if (ctx->start == -1)
			ctx->start = *i;
	}
	else if (ctx->start == -1)
		ctx->start = *i;
}

char	**smart_split(const char *line)
{
	t_split_ctx		ctx;
	unsigned char	state;
	int				i;

	ctx.line = line;
	ctx.capacity = 8;
	ctx.count = 0;
	ctx.start = -1;
	ctx.tokens = malloc(sizeof(char *) * ctx.capacity);
	if (!ctx.tokens)
		return (NULL);
	state = 0;
	i = 0;
	while (line[i])
	{
		process_char(&ctx, &state, &i);
		i++;
	}
	flush_token(&ctx, i);
	ctx.tokens[ctx.count] = NULL;
	return (ctx.tokens);
}
