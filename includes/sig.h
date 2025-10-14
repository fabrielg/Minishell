/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 21:26:53 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/10/14 21:26:54 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
void	handle_sigquit(int sig);

#endif
