#include "minishell.h"
#include "parser.h"
#include "exec.h"
#include "ast.h"
#include <readline/history.h>

pid_t	g_sig_pid = 0;

/**
 * @brief Checks if the input line signals EOF (Ctrl-D).
 * @return 1 if EOF, 0 otherwise
 */
int	is_end_of_file(char *input_line)
{
	if (input_line)
		return (0);
	write(STDOUT_FILENO, "exit\n", 5);
	return (1);
}

/**
 * @brief Processes a single input line in the minishell.
 * @return 0 on success, error code on failure
 */
int	process_line(t_minishell *ms)
{
	if (!*ms->input_line)
		return (0);
	ms->tokens = parser(ms);
	if (ms->input_line && ms->input_line[0])
		add_history(ms->input_line);
	if (!ms->tokens && ms->input_line && ms->input_line[0])
	{
		if (ms->last_exit_code != 2)
			set_err(&ms->last_exit_code, 1);
		return (1);
	}
	if (DEBUG_MODE)
		tokens_display(ms->tokens);
	ms->ast_root = ast_build(ms->tokens);
	if (DEBUG_MODE)
		ast_display(ms->ast_root);
	exec_ast(ms->ast_root, ms);
	ast_clear(&ms->ast_root);
	ft_lstclear2(&ms->tokens, token_destroy);
	return (0);
}

/**
 * @brief Handles signals received while waiting at the prompt.
 */
void	handle_prompt_signal(t_uint8 *exit_code)
{
	if (g_sig_pid != -1)
		return ;
	g_sig_pid = 0;
	*exit_code = 130;
}
