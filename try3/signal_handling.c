#include "ft_select.h"
#include <signal.h>


int	g_sigresize = 0;

static void	resize_handler(void)
{
	g_sigresize = 1;
}

static void	signal_dispatcher(int signo)
{
	
	if (signo == SIGINT)
	{
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

	if (signal(SIGWINCH, signal_dispatcher) ==  SIG_ERR)
		ft_printf("error\n");
}
