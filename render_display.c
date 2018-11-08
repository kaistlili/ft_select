#include "ft_select.h"



/*
	1-recover initial cursor pos
	2-calculate max columns we can print max_col;
	3- 





*/


/*
	optimal columns count:
	char **tab = &av[1];

	1- get maxlen
	2- NOT_recursive(char **tab, len, ws_col)
		{
			int n_col;

			
		}
*/

void	ft_pad(int len, int col)
{
	int pad;

	pad = (col - len) / 2;
	while(pad)
	{
		write(1, " ", 1);
		pad--;
	}
}

void	render_item(t_item *item)
{
	
	ft_pad(ft_strlen(item->text), g_display.win_sz.ws_col);
	if (item->selected > 0)
		tputs(tgetstr("mr", NULL), 1, ft_iputchar);
	if (g_display.current == item)
		tputs(tgetstr("us", NULL), 1, ft_iputchar);
	tputs(tgetstr("cd", NULL), 1, ft_iputchar);
	write(1, item->text, ft_strlen(item->text));
	write(1, "\n", 1);
	if (item->selected > 0)
		tputs(tgetstr("me", NULL), 1, ft_iputchar);
	if (g_display.current == item)
		tputs(tgetstr("ue", NULL), 1, ft_iputchar);
	
}

void	reinit_cursor()
{
	int	count;

	count = g_display.count;	
	while (count)
	{
		count--;
		tputs(tgetstr("up", NULL), 1, ft_iputchar);
	}
	tputs(tgetstr("cr", NULL), 1, ft_iputchar);
}

void	clear_our_mess(void)
{
	int	count;

	count = g_display.count;	
	while (count)
	{
		count--;
		tputs(tgetstr("cd", NULL), 1, ft_iputchar);
		tputs(tgetstr("do", NULL), 1, ft_iputchar);

	}
	tputs(tgetstr("cd", NULL), 1, ft_iputchar);
	tputs(tgetstr("cr", NULL), 1, ft_iputchar);
	reinit_cursor();
}

void	render_display(void)
{
	t_item *start;
	int	count;

//	tputs(tgetstr("rc", NULL), 1, ft_iputchar);
	count = 0;
	start = *(g_display.head);
	while (count < g_display.count)
	{
		render_item(start);
		start = start->next;
		count++;
	}
	reinit_cursor();
}
