#include "ft_select.h"

int	frames = 0;

/*
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
*/
/*

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
*/
/* we need to figure out why cursor reinit is broken */

void	print_item(t_item item, int current, unsigned int ws_col)
{
	if (item.selected > 0)
		tputs(tgetstr("mr", NULL), 1, ft_iputchar);
	if (current)
		tputs(tgetstr("us", NULL), 1, ft_iputchar);
	tputs(tgetstr("ce", NULL), 1, ft_iputchar);
	write(1, item.text, item.len);
	ft_printf("F:%D", ws_col);
	if (item.selected > 0)
		tputs(tgetstr("me", NULL), 1, ft_iputchar);
	if (current)
		tputs(tgetstr("ue", NULL), 1, ft_iputchar);
	
}

void	clear_our_mess(void)
{
	tputs(tgetstr("cd", NULL), 1, ft_iputchar);
}

unsigned int
	get_max_len(t_item	*items, unsigned int count, unsigned int  ws_row, unsigned int *cols_len)
{
	unsigned int 	i;
	unsigned int	ret;
	unsigned int	col_max_len;

	i = 0;
	ret = 0;
	col_max_len = 0;
	while (i < count)
	{
		if (items[i].len > col_max_len)
			col_max_len = items[i].len;
		i++;
		if (((i % ws_row) == 0) || (i  == count))
		{
			if ((i >= ws_row) && (i != count))
				ret = ret + 2;
			*cols_len = col_max_len;
			cols_len++;
			ret = ret + col_max_len;
		}
	}
	return (ret);
}

void	restore_exit()
{
	restore_tcap();
	exit(1);
}

unsigned int	*col_size(t_display *display)
{
	unsigned int	cols_nbr;
	unsigned int	*cols_len;
	size_t			tot_max_len;

	cols_nbr = 	display->count / display->win_sz.ws_row;
	if (display->count % display->win_sz.ws_row)
		cols_nbr++;
	cols_len = malloc(sizeof(unsigned int) * (1 + cols_nbr));
	if (cols_len == NULL)
		restore_exit();
	cols_len[cols_nbr] = 0;
	tot_max_len = get_max_len(display->items, display->count, display->win_sz.ws_row, cols_len);	
	if (tot_max_len > display->win_sz.ws_col)
	{
		free(cols_len);
		return (NULL);
	}	
	return (cols_len);
}

int running = 0;

void	render_display(t_display display)
{
	unsigned int	count;
	unsigned int	*col;

ft_printf("E%d|",frames);frames++;
//	if (running){ft_printf("FATAL ERROR");exit(1);}
	running = 1;
	count = 0;
	if ((col = col_size(&display)) == NULL)
		return;
/*	else
	{ft_printf("col %d", col);
		tputs(tgoto(tgetstr("ch", NULL), 0, 0), 1, ft_iputchar);
	return;
	}*/
	while (count < display.count)
	{
		if (count == display.index)
			print_item(display.items[count], 1, display.win_sz.ws_row);
		else
			print_item(display.items[count], 0, display.win_sz.ws_row);
//		sleep(1);
		count++;	
		set_cursor(display, count, col);
	}
	running = 0;
}
