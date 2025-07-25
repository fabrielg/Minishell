/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BST.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 19:31:22 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/07/25 21:04:15 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	BST_H
# define BST_H

typedef struct s_tree	t_tree;
struct s_tree
{
	int		value;
	t_tree	*left_child;
	t_tree	*right_child;
};

void	bs_display(t_tree *tree);
t_tree	*bs_new(int value, t_tree *left, t_tree *right);
t_tree	*bs_search(t_tree *tree, int to_find);
int		bs_insertion(t_tree **tree, int value);
void	bs_clear(t_tree *tree);

#endif