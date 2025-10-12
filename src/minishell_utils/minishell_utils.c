#include "minishell.h"
#include "exec.h"

/**
 * @brief Initializes minishell.
 * @param ms   Minishell context to initialize
 * @param envp Environment variables from system
 */
void	init_minishell(t_minishell *ms, char **envp)
{
	ft_bzero(ms, sizeof(t_minishell));
	ms->exports = mst_alloc_env(envp);
	ms->stdin_backup = dup(STDIN_FILENO);
	ms->stdout_backup = dup(STDOUT_FILENO);
	ms->shell_exit_code = -1;
	ms->in_pipe = false;
	ms->signal_received = false;
	if (DEBUG_MODE)
		ms->shell_name = BLUE_B"Minichaise (debug) 🪑: "RESET;
	else
		ms->shell_name = WHITE_B"Minichaise 🪑: "RESET;
}

/**
 * @brief Frees minishell resources and restores state before exit.
 * @param ms        Minishell context
 * @param exit_code Shell exit code to return
 * @return The given exit_code
 */
t_uint8	clear_minishell(t_minishell *ms, t_uint8 exit_code)
{
	mst_clear(&ms->exports);
	ast_clear(&ms->ast_root);
	ft_lstclear2(&ms->tokens, token_destroy);
	if (ms->input_line)
		free(ms->input_line);
	ms->input_line = NULL;
	if (ms->stdin_backup)
		close(ms->stdin_backup);
	if (ms->stdout_backup)
		close(ms->stdout_backup);
	return (exit_code);
}
