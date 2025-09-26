#include "minishell.h"
#include "sig.h"
#include <readline/readline.h>
#include <readline/history.h>

void	handle_sigint(int sig)
{
	(void)sig;
	write(STDIN_FILENO, "\n", 1);
	if (g_sig_pid > 0)
	{
		kill(g_sig_pid, sig);
		return ;
	}
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_sig_pid = -1;
}

void	init_signals(void)
{
	g_sig_pid = 0;
	signal(SIGINT, &handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	reset_signals(void)
{
	g_sig_pid = 0;
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
