#include "ft_select.h"

void	set_cursor(t_display display, int current, unsigned int *col_len)
{
	unsigned int	ws_row;
	static	unsigned int tot = 0;
	static	unsigned int i = 0;

	if (current == 0)
		return;
	ws_row = display.win_sz.ws_row;
	if (current == display.count)
	{
	//last element
/*		while ((current % ws_row) != 1)
		{
			tputs(tgetstr("up", NULL), 1, ft_iputchar);
			current--;
		}		i = 0;
		tputs(tgoto(tgetstr("ch", NULL), 0, 60), 1, ft_iputchar);
		tputs(tgetstr("cr", NULL), 1, ft_iputchar);*/
		i = 0;
		tot = 0;	
		tputs(tgoto(tgetstr("cm", NULL), 0, 0), 1, ft_iputchar);
		return;
	}
	if ((current % ws_row) == 0)
	{
	//last in col
		while ((current % ws_row) != 1)
		{
			tputs(tgetstr("up", NULL), 1, ft_iputchar);
			current--;
		}
		tot = tot + 2 + col_len[i];
		tputs(tgoto(tgetstr("ch", NULL), 0, tot), 1, ft_iputchar);
		i++;
	}
	else
	{
		tputs(tgetstr("do", NULL), 1, ft_iputchar);
//		if (tot != 0)
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
