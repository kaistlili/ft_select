#include "ft_select.h"

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

	if (g_display.count <= g_display.win_sz.ws_row)
		count = g_display.count - 1;	
	else
		count = g_display.win_sz.ws_row - 1;
	while (count > 0)
	{
		count--;
		tputs(tgetstr("up", NULL), 1, ft_iputchar);
	}
	tputs(tgetstr("cr", NULL), 1, ft_iputchar);
}

void	up_n_lines(int n_lines)
{
	int	count;

//	n_lines--;
	tputs(tgetstr("cr", NULL), 1, ft_iputchar);
	while (n_lines-- > 0)
{	//	tputs(tgetstr("up", NULL), 1, ft_iputchar);
		tputs(tgetstr("sr", NULL), 1, ft_iputchar);

}
}

void	clear_our_mess(void)
{
	tputs(tgetstr("cd", NULL), 1, ft_iputchar);
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
			return (cols++);
	}
	return (cols);	
}

int	nbr_columns(void)
{
	int	max_len;
	t_item	*start;

	start = g_display.current; 
	if ((g_display.count) > g_display.win_sz.ws_row)
	{
		return(get_nbr_columns());
	}
	if (text_max_len(&start, g_display.count) > g_display.win_sz.ws_col)
		return (0);
	return (1);
}

void	scroll_n_lines(int n_lines, int to_scroll, char *direction)

{
	int	count;

	while (n_lines-- > 0)
{	
		tputs(tgetstr("up", NULL), 1, ft_iputchar);
		if (n_lines <= to_scroll)
			tputs(tgetstr("sr", NULL), 1, ft_iputchar);
}
	tputs(tgetstr("cr", NULL), 1, ft_iputchar);
}

/* we need to figure out why cursor reinit is broken */

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
//	if ((col = nbr_columns()) == 0)
//	{
//		ft_printf("not enough space");
//		tputs(tgoto(tgetstr("ch", NULL), 0, padding), 1, ft_iputchar);
//		return;
//	}
//	ft_printf("nbr item %d nbr col %d\n", g_display.count, col);
//	return ;
	g_display.f_writing = 1;
	count = 0;
	start = *(g_display.head);
	tmp = start; // col counter
	ws_row = g_display.win_sz.ws_row;
	while (count < g_display.count)
	{
		tputs(tgoto(tgetstr("ch", NULL), 0, padding), 1, ft_iputchar);
		print_item(start);
		start = start->next;
		count++;
		if (count != g_display.count)
		{
			if (((count % ws_row) == 0) && (count != 0))
			{
				padding = padding + text_max_len(&tmp, ws_row) + 2;
				up_n_lines((count - 1) % ws_row );
			}
			else	
				tputs(tgetstr("do",NULL), 1, ft_iputchar);
		}	
	}
//	tputs(tgetstr("rc", NULL), g_display.win_sz.ws_col, ft_iputchar);
	//up_n_lines((count - 1) % ws_row );
	//if (g_display.win_sz.ws_row > ws_row){ exit(1);
	//	scroll_n_lines((count -1) % ws_row, g_display.win_sz.ws_row - ws_row, "up");}
//	else
		up_n_lines((count - 1) % ws_row);
	g_display.lines_wrote = count % ws_row;
//	reinit_cursor();

	g_display.f_writing = 0;
}
