#include "ft_select.h"
#include <signal.h>

void	scroll_lines_up(int n_lines)
{
	while (n_lines)
	{
		tputs(tgetstr("sr", NULL), 1, ft_iputchar);
		tputs(tgetstr("up", NULL), 1, ft_iputchar);
		n_lines--;
	}
}

void	resize_handler(void)
{
	static int running = 0;

	if (running)
		return;
	running = 1;
	if (g_display.f_writing)
	{ft_printf("signal caught\n");exit(1);return;}
	if (ioctl(0, TIOCGWINSZ, &(g_display.win_sz)) == -1)
	{
		ft_printf("ioctl request error\n");
		exit(1);
	}
//	if (g_display.win_sz.ws_row < g_display.lines_wrote){
//		ft_printf("case 2 %d %d\n", g_display.win_sz.ws_row, g_display.lines_wrote);exit(1);
//		scroll_lines_up(g_display.lines_wrote - g_display.win_sz.ws_row);}
	clear_our_mess();
	render_display();
	running = 0;
}

void	signal_dispatcher(int signo)
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
