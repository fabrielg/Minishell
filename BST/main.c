/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabrielg <fabrielg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 17:24:35 by fabrielg          #+#    #+#             */
/*   Updated: 2025/08/17 17:30:35 by fabrielg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BST.h"
#include <stdlib.h>
#include <stdio.h>

int	main(void)
{
	t_tree	*tree = bs_new(26, bs_new(11, bs_new(1, NULL, NULL), bs_new(16, NULL, NULL)), bs_new(35, NULL, bs_new(41, NULL, NULL)));
	bs_display(tree);
	t_tree	*find = bs_search(tree, 35);
	t_tree	*not_find = bs_search(tree, 14);
	printf("find: %d\n", find->value);
	bs_display(find);
	printf("not find: %p\n", not_find);
	bs_display(not_find);
	bs_clear(tree);
	return (0);
}