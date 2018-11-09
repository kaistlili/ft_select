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

void	print_item(t_item *item)
{
	
	//ft_pad(ft_strlen(item->text), g_display.win_sz.ws_col);
	if (item->selected > 0)
		tputs(tgetstr("mr", NULL), 1, ft_iputchar);
	if (g_display.current == item)
		tputs(tgetstr("us", NULL), 1, ft_iputchar);
	tputs(tgetstr("ce", NULL), 1, ft_iputchar);
	write(1, item->text, ft_strlen(item->text));
	if (item->selected > 0)
		tputs(tgetstr("me", NULL), 1, ft_iputchar);
	if (g_display.current == item)
		tputs(tgetstr("ue", NULL), 1, ft_iputchar);
	
}

void	reinit_cursor()
{
	int	count;

	if (g_display.count < g_display.win_sz.ws_row)
		count = g_display.count /*- 1*/;	
	else
		count = g_display.win_sz.ws_row/* - 1*/;
	while (count > 0)
	{
		count--;
		tputs(tgetstr("up", NULL), 1, ft_iputchar);
	}
	tputs(tgetstr("cr", NULL), 1, ft_iputchar);
}

void	clear_our_mess(void)
{
	int	count;

	if (g_display.count < g_display.win_sz.ws_row)
		count = g_display.count/* - 1*/;
	else
		count = g_display.win_sz.ws_row /* - 1 */ ;
		tputs(tgetstr("cd", NULL), 1, ft_iputchar);
	while (count > 0)
	{
		count--;
		tputs(tgetstr("do", NULL), 1, ft_iputchar);

	}
	tputs(tgetstr("cr", NULL), 1, ft_iputchar);
	reinit_cursor();
}

int	text_tot_len(void)
{
	int 	i;
	int	tot_len;
	t_item *start;
	

	tot_len = 0;
	start = *(g_display.head);
	i = 0;	
	while (i < g_display.count)
	{
		tot_len = tot_len + start->len;
		start = start->next;
		i++;
	}
	return (tot_len);
}

int	text_max_len(t_item **start, int count)
{
	int 	i;
	int	max_len;
	

	max_len = 0;
	i = 0;	
	while (i < count)
	{
		if (max_len < ft_strlen((*start)->text))
			max_len = ft_strlen((*start)->text);
		*start = (*start)->next;
		if (*start == *(g_display.head))
			return (max_len);
		i++;
	}
	return (max_len);
}

int	get_nbr_columns(void)
{
	int 	cols;
	int	next_maxlen;
	int	ws_row;
	int	ws_col_left;
	int	items_left;
	t_item	*start;	


	cols = 0;
	start = *(g_display.head);
	ws_row = g_display.win_sz.ws_row;
	next_maxlen = text_max_len(&start, ws_row);
	ws_col_left = g_display.win_sz.ws_col - next_maxlen;
	if (ws_col_left <= 0)
		return (0);
	while (ws_col_left > 0) 
	{
		cols++;
		next_maxlen = text_max_len(&start, ws_row) + 2; //+2 for pad
		if (next_maxlen > ws_col_left)
			return (0);
		ws_col_left = ws_col_left - next_maxlen;
		if (start == *(g_display.head))
			return (cols);
	}
	return (cols);	
}

int	nbr_columns(void)
{
	int	max_len;
	t_item	*start;

	start = g_display.current; 
	if ((g_display.count + 1) > g_display.win_sz.ws_row)
	{
		return(get_nbr_columns());
	}
	if (text_max_len(&start, g_display.count) > g_display.win_sz.ws_col)
		return (0);
	return (1);
}

void	next_col(int toskip)
{
		
}

void	render_display(void)
{
	t_item *start;
	t_item *tmp;
	int	count;
	int	col;
	int	ws_row;
	int	padding = 0;
	//ft_printf("tot len %d matrix %d\n", text_tot_len(), text_tot_len() * g_display.count);
//	if (
	if ((col = nbr_columns()) == 0)
	{
		return;
	}
	count = 0;
	start = *(g_display.head);
	tmp = start; // col counter
	ws_row = g_display.win_sz.ws_row;
	while (count < g_display.count)
	{
		if (((count % ws_row) == 0) && (count != 0))
		{
			padding = padding + text_max_len(&tmp, ws_row) + 2;
			reinit_cursor();
		}
		else 
		{
			tputs(tgetstr("do",NULL), 1, ft_iputchar);
		}
		tputs(tgoto(tgetstr("ch", NULL), 0, padding), 1, ft_iputchar);
	//	write(1,"*",1);
		print_item(start);
	//	write(1,"5",1);
		start = start->next;
		count++;
	}
	reinit_cursor();
}
