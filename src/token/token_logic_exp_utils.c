#include "tokens.h"

t_token	*token_create_logic_exp(t_logical_op op, t_token *left, t_token *right)
{
	t_token					*token;
	t_logical_expression	*logic_exp;

	token = (t_token *) malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	logic_exp = (t_logical_expression *) malloc(sizeof(t_logical_expression));
	if (!logic_exp)
		return (free(token), NULL);
	logic_exp->op = op;
	logic_exp->left = left;
	logic_exp->right = right;
	token->type = TOKEN_LOGICAL_EXPRESSION;
	token->data.logical_expr = logic_exp;
	return (token);
}

void	token_destroy_logic_exp(t_logical_expression *logic_exp)
{
	if (!logic_exp)
		return ;
	// TODO: free logic_exp->left
	// TODO: free logic_exp->right
	free(logic_exp);
}