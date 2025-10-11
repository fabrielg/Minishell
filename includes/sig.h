#ifndef SIG_H
# define SIG_H

# include <sys/types.h>
# include <signal.h>

extern pid_t	g_sig_pid;

//[SIGNALS]________________________________

void	init_signals(void);
void	reset_signals(void);
void	handle_sigint(int sig);
void	handle_sigint_pipeline(int sig);

#endif
