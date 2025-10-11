#include "smart_split.h"
#include <stdlib.h>
#include "lexer.h"

/**
 * @brief Ensures the token array has enough capacity and reallocates if needed.
 * @return 1 on success, 0 on allocation failure
 */
static int	ensure_capacity(t_split_ctx *ctx)
{
	char	**new_tokens;
	int		i;

	if (ctx->count < ctx->capacity - 1)
		return (1);
	ctx->capacity *= 2;
	new_tokens = malloc(sizeof(char *) * ctx->capacity);
	if (!new_tokens)
		return (0);
	i = 0;
	while (i < ctx->count)
	{
		new_tokens[i] = ctx->tokens[i];
		i++;
	}
	free(ctx->tokens);
	ctx->tokens = new_tokens;
	return (1);
}

/**
 * @brief Flushes the current token from start to end into the tokens array.
 */
void	flush_token(t_split_ctx *ctx, int end)
{
	if (ctx->start == -1)
		return ;
	ctx->tokens[ctx->count++] = substr(ctx->line, ctx->start, end);
	ctx->start = -1;
	ensure_capacity(ctx);
}

/**
 * @brief Flushes an operator token into the tokens array and updates index.
 */
void	flush_operator(t_split_ctx *ctx, int *i)
{
	int	oplen;

	oplen = operator_len(ctx->line, *i);
	ctx->tokens[ctx->count++] = substr(ctx->line, *i, *i + oplen);
	ensure_capacity(ctx);
	*i += oplen - 1;
}
