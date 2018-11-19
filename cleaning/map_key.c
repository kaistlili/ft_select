#include "ft_select.h"

void	restore_exit(t_display *display)
{
	(void)display;
	restore_tcap();
	exit(1);
}
/*
void	clear_our_mess(void)
{
//	tputs(tgetstr("ho", NULL), 1, ft_iputchar);
	tputs(tgetstr("cl", NULL), 1, ft_iputchar);
//	tputs(tgetstr("ho", NULL), 1, ft_iputchar);
}
*/
void	clear_our_mess(void)
{	
	struct	winsize	win_sz;

	if (ioctl(0, TIOCGWINSZ, &win_sz) == -1)
		restore_exit(NULL);
	tputs(tgetstr("ho", NULL), 1, ft_iputchar);
	while (win_sz.ws_row)
	{
		tputs(tgetstr("dl", NULL), 1, ft_iputchar);
//		sleep(1);
		win_sz.ws_row = win_sz.ws_row - 1;
	}
}

void	select_current(t_display *display)
{
	display->items[display->index].selected = -display->items[display->index].selected;
	move_down(display);
}

void	delete_item(t_display *display, int index)
{
	size_t start;

	start = index + 1;
	while (start < display->count)
	{
		ft_memmove(display->items + start - 1, display->items + start, sizeof(t_item));
		start++;
	}
	display->count = display->count - 1;
	if (display->count == 0)
		return;
	if ((display->index) >= display->count)
		display->index = (display->index) % display->count;	
	return;
}

void	return_selected(t_display *display)
{
	(void)display;
}

void	delete_selected(t_display *display)
{
	size_t i;
	unsigned int save;

	save = display->index;
	i = 0;
	while (i < display->count)
	{
		if (display->items[i].selected > 0)
			delete_item(display, i);
		else
			i++;
	}
	if (display->count == 0)
		return;
}

void	delete_current(t_display *display)
{
	delete_item(display, display->index);
}

void	move_up(t_display *display)
{

		if (display->index == 0)
			display->index = display->count - 1;
		else
			display->index = display->index - 1;
}

void	move_down(t_display *display)
{

		display->index = (display->index + 1) % display->count;
}

void	move_left(t_display *display)
{
	if (display->index < display->win_sz.ws_row) 
	{
		display->index = (display->index + ((display->count / display->win_sz.ws_row) * display->win_sz.ws_row));
		if (display->index >= display->count)
			move_left(display);
	}
	else
		display->index = display->index - display->win_sz.ws_row;
}

void	move_right(t_display *display)
{

	if ((display->index + display->win_sz.ws_row) >= display->count)
		display->index = display->index  % display->win_sz.ws_row;
	else
		display->index = display->index + display->win_sz.ws_row;
}
