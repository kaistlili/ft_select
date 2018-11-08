#include "ft_select.h"
#include <signal.h>

void	resize_handler(void)
{

}

void	signal_dispatcher(int signo)
{
	
	if (signo == SIGINT)
	{
/*		if (ioctl(0, TIOCGWINSZ, &(g_display.win_sz)) == -1)
		{
			ft_printf("ioctl request error\n");
			exit(1);
		}
	ft_printf("sizeof term ws_col %d ws_row %d\n", g_display.win_sz.ws_col, g_display.win_sz.ws_row);
		*/
		restore_tcap();
		exit(1);
	}
	else if (signo == SIGWINCH)
		resize_handler();
}


void	set_signals(void)
{
	
	if (signal(SIGINT, signal_dispatcher) ==  SIG_ERR)
		ft_printf("error\n");
}
