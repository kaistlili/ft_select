#include "ft_select.h"


void	reinit_cursor(void)
{
	
}

void	set_cursor(t_display display, int current, unsigned int *col_len)
{
	unsigned int	ws_row;
	static	unsigned int tot = 0;
	static	unsigned int i = 0;

	ws_row = display.win_sz.ws_row;
	if (current == display.count)
	{
	//last item we reset cursor
		i = 0;
		tot = 0;	
		tputs(tgoto(tgetstr("cm", NULL), 0, 0), 1, ft_iputchar);
		return;
	}
	if (((current % ws_row) == 0) && (current != 0))
	{
	//last in col
		tputs(tgoto(tgetstr("cm", NULL), 0, 0), 1, ft_iputchar);
		tot = tot + 2 + col_len[i];
		i++;
		tputs(tgoto(tgetstr("ch", NULL), 0,
			 tot + ((col_len[i] - display.items[current].len) / 2)), 1, ft_iputchar);
	}
	else
	{
		if (current != 0)
			tputs(tgetstr("do", NULL), 1, ft_iputchar);
		tputs(tgoto(tgetstr("ch", NULL), 0,
			 tot + ((col_len[i] - display.items[current].len) / 2)), 1, ft_iputchar);
	}
}


/*
	each line we print i, i + ws_row until (i + ws_row) > count

	printline(display, line)
	{
		print_item(display.item[i]);
		while ((i = i + ws_row) < display.count)
		{
			
		}
	}
	
	while(i < (count % ws_row))
	{
		printline(display, i);
		i++;
	}



*/
