/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 16:06:26 by ktlili            #+#    #+#             */
/*   Updated: 2018/11/29 17:14:05 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"
#include <signal.h>

int	g_sigresize = 0;
int	g_foreground = 1;

static	void	resize_handler(void)
{
	g_sigresize = 1;
}

static	void	goto_background(void)
{
	char			ctrl_z[2];
	struct termios	*termios_st;

	restore_tcap();
	if (signal(SIGTSTP, SIG_DFL) == SIG_ERR)
		ft_printf("error\n");
	termios_st = termios_set();
	ctrl_z[0] = termios_st->c_cc[VSUSP];
	ioctl(0, TIOCSTI, ctrl_z);
	write(0, "\r  ", 3);
}

static	void	goto_foreground(void)
{
	init_tcap();
	if (signal(SIGTSTP, signal_dispatcher) == SIG_ERR)
		ft_printf("error\n");
	g_foreground = 1;
}

void			signal_dispatcher(int signo)
{
	if (signo == SIGWINCH)
		resize_handler();
	else if (signo == SIGTSTP)
		goto_background();
	else if (signo == SIGCONT)
		goto_foreground();
	else
		restore_exit(NULL);
}

void			set_exit_signals(void)
{
	signal(SIGINT, signal_dispatcher);
	signal(SIGQUIT, signal_dispatcher);
	signal(SIGTERM, signal_dispatcher);
	signal(SIGABRT, signal_dispatcher);
	signal(SIGHUP, signal_dispatcher);
	signal(SIGPIPE, signal_dispatcher);
	signal(SIGILL, signal_dispatcher);
	signal(SIGTRAP, signal_dispatcher);
	signal(SIGEMT, signal_dispatcher);
	signal(SIGFPE, signal_dispatcher);
	signal(SIGBUS, signal_dispatcher);
	signal(SIGSEGV, signal_dispatcher);
	signal(SIGSYS, signal_dispatcher);
	signal(SIGALRM, signal_dispatcher);
	signal(SIGTTIN, signal_dispatcher);
	signal(SIGTTOU, signal_dispatcher);
	signal(SIGXCPU, signal_dispatcher);
	signal(SIGXFSZ, signal_dispatcher);
	signal(SIGVTALRM, signal_dispatcher);
	signal(SIGPROF, signal_dispatcher);
	signal(SIGUSR1, signal_dispatcher);
	signal(SIGUSR2, signal_dispatcher);
}

void			set_signals(void)
{
	signal(SIGWINCH, signal_dispatcher);
	signal(SIGTSTP, signal_dispatcher);
	signal(SIGCONT, signal_dispatcher);
	set_exit_signals();
}
