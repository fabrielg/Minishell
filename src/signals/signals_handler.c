#include "minishell.h"
#include "sig.h"
#include <readline/readline.h>
#include <readline/history.h>

/**
 * @brief Handles SIGINT (Ctrl+C) in interactive shell.
 *        Sends signal to child if running, otherwise refreshes prompt.
 * @param sig Signal number (unused)
 */
void	handle_sigint(int sig)
{
	(void)sig;
	if (g_sig_pid > 0)
	{
		kill(g_sig_pid, sig);
		return;
	}
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_sig_pid = -1;
}

void	handle_sigint_pipeline(int sig)
{
	(void)sig;
	if (g_sig_pid > 0)
		kill(g_sig_pid, sig);
}

/**
 * @brief Initializes signal handlers for interactive shell.
 *        SIGINT is custom, SIGQUIT is ignored.
 */
void	init_signals(void)
{
	g_sig_pid = 0;
	signal(SIGINT, &handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

/**
 * @brief Resets signal handlers to default behavior.
 */
void	reset_signals(void)
{
	g_sig_pid = 0;
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
