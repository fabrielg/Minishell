#ifndef SIG_H
# define SIG_H

# include <sys/types.h>
# include <signal.h>

extern pid_t g_sig_pid;

void		init_signals(void);
void		check_last_sig(t_uint8 *exit_code);
void		reset_signals(void);

#endif
