#include "ft_select.h"


static	void	reinit_cursor(unsigned int *col_index, unsigned int *tot_pad, char *cm)
{
	*col_index = 0;
	*tot_pad = 0;	
	tputs(tgoto(cm, 0, 0), 1, ft_iputchar);
//	tputs(tgetstr("ho", NULL), 1, ft_iputchar);
	return;
}

void	set_cursor(t_display display, unsigned int current, unsigned int *col_len)
{
	unsigned int	ws_row;
	static	unsigned int tot_pad = 0;
	static	unsigned int col_index = 0;
	static	char		*cm = NULL;
	static	char		*ch = NULL;

	if (cm == NULL)
	{
		cm = tgetstr("cm", NULL);
		ch = tgetstr("ch", NULL);
	}
	ws_row = display.win_sz.ws_row;
	if (current == display.count)
	{
		reinit_cursor(&col_index, &tot_pad, cm);
		return;
	}
	if (((current % ws_row) == 0) && (current != 0))
	{
		tot_pad = tot_pad + 2 + col_len[col_index];
		col_index++;
		tputs(tgoto(cm, tot_pad + ((col_len[col_index] - display.items[current].len) / 2), 0), 1, ft_iputchar);
		//tputs(tgoto(tgetstr("ch", NULL), 0, tot_pad + ((col_len[col_index] - display.items[current].len) / 2)), 1, ft_iputchar);
	}
	else
	{
		if (current != 0)
			tputs(/*tgetstr("do", NULL)*/ "\n", 1, ft_iputchar);
		tputs(tgoto(ch, 0,
			 tot_pad + ((col_len[col_index] - display.items[current].len) / 2)), 1, ft_iputchar);
	}
}
