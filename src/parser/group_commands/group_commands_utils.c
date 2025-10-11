#include "tokens.h"
#include "parser.h"

/**
 * @brief Adds the current command to the result list and resets it.
 */
void	flush_command(t_list2 **result, t_command **current)
{
	if (*current)
	{
		ft_lstadd_back2(result, ft_lstnew2(token_create_command(*current)));
		*current = NULL;
	}
}
