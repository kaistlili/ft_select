#include "ft_select.h"
#include <signal.h>

//temp g var
extern	t_display	*g_screen;
extern	int			g_writing;

int	g_sigresize = 0;
int	g_foreground = 0;
/*
static void	resize_handler(void)
{
//	if ((g_sigresize) || (g_writing))
//		return;
	g_sigresize = 1;
	ioctl(0, TIOCGWINSZ, &(g_screen->win_sz));
	clear_our_mess(*g_screen);
	render_display(*g_screen);
	g_sigresize = 0;
}
*/
static	void	goto_background(void)
{
	char	ctrl_z[2];
	struct	termios	*termios_st;

	restore_tcap();
	if (signal(SIGTSTP, SIG_DFL) ==  SIG_ERR)
		ft_printf("error\n");
	termios_st = termios_set();
	ctrl_z[0] = termios_st->c_cc[VSUSP];
	ioctl(0, TIOCSTI, ctrl_z);
	write(0, "\r  ", 3);
}

static	void	goto_foreground(void)
{
	init_tcap();
	if (signal(SIGTSTP, signal_dispatcher) ==  SIG_ERR)
		ft_printf("error\n");
	g_foreground = 1;
}

void	signal_dispatcher(int signo)
{
	
	if (signo == SIGINT)
	{
		restore_tcap();
		exit(1);
	}
//	else if (signo == SIGWINCH)
//		resize_handler();
	else if (signo == SIGTSTP)
		goto_background();
	else if (signo == SIGCONT)
		goto_foreground();
}


void	set_signals(void)
{
	
	if (signal(SIGINT, signal_dispatcher) ==  SIG_ERR)
		ft_printf("error\n");
	if (signal(SIGWINCH, signal_dispatcher) ==  SIG_ERR)
		ft_printf("error\n");
	if (signal(SIGTSTP, signal_dispatcher) ==  SIG_ERR)
		ft_printf("error\n");
	if (signal(SIGCONT, signal_dispatcher) ==  SIG_ERR)
		ft_printf("error\n");
}
