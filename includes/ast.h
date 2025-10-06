/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-abr <alde-abr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 00:31:16 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/09/08 16:35:52 by alde-abr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "tokens.h"

typedef struct s_ast	t_ast;
struct s_ast
{
	t_token_type	type;
	union
	{
		t_command	*cmd;
		struct
		{
			int				count;
			struct s_ast	**cmds;
		}	pipeline;
		struct
		{
			t_logical_op	op;
			struct s_ast	*left;
			struct s_ast	*right;
		}	logical;
		t_ast	*subshell;
	};
};

t_ast	*ast_build(t_list2 *tokens);
t_ast	*ast_new_command(t_command *cmd);
t_ast	*ast_new_pipeline(t_ast **cmds, size_t count);
t_ast	*ast_new_logical(t_logical_op op, t_ast *left, t_ast *right);
t_ast	*ast_new_subshell(t_ast *sub);
void	ast_display(t_ast *node);
void	ast_clear(t_ast **root);

int		assign_pipes(t_ast *node);

#endif
