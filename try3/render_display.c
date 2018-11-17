#include "ft_select.h"

void	print_item(t_item item, int current, unsigned int ws_col)
{
	if (item.selected > 0)
		tputs(tgetstr("mr", NULL), 1, ft_iputchar);
	if (current)
		tputs(tgetstr("us", NULL), 1, ft_iputchar);
	tputs(tgetstr("ce", NULL), 1, ft_iputchar);
	write(1, item.text, item.len);
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

void	render_display(t_display display)
{
	unsigned int	count;
	unsigned int	*col;

	count = 0;
	if ((col = col_size(&display)) == NULL)
	{
		clear_our_mess();
		return;
	}
	set_cursor(display, count, col);
	while (count < display.count)
	{
		if (count == display.index)
			print_item(display.items[count], 1, display.win_sz.ws_row);
		else
			print_item(display.items[count], 0, display.win_sz.ws_row);
		count++;	
		set_cursor(display, count, col);
	}
//	free(col);
}
