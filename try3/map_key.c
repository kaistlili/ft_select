#include "ft_select.h"

void	select_current(t_display *display)
{
	display->items[display->index].selected = -display->items[display->index].selected;
	move_down(display);
}

void	delete_item(t_display *display, int index)
{
	int start;

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

}

void	delete_selected(t_display *display)
{
	int i;
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
//	if (display->index >= display->count)
//	display->index = 0;
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
/*
void	map_esc(char *buff, int read_count, t_display *display)
{
	if (!ft_strcmp(tgetstr("kD", NULL), buff))
	{
	//	delete_current(display);
		delete_item(display, display->index);
	} 
	if (read_count == 1)
	{
		restore_tcap();
		exit(1);
	}
	if (!ft_strncmp(buff + 1,"[D", 2))
	{
	}
	else if (!ft_strncmp(buff + 1,"[A",2))
	{
		if (display->index == 0)
			display->index = display->count - 1;
		else
			display->index = display->index - 1;
	}
	else if (!ft_strncmp(buff + 1,"[C",2))
	{
		if ((display->index + display->win_sz.ws_row) >= display->count)
			display->index = display->index  % display->win_sz.ws_row;
		else
			display->index = display->index + display->win_sz.ws_row;
	}
	else if (!ft_strncmp(buff + 1,"[B",2))
	{
		display->index = (display->index + 1) % display->count;
	}
}



void	map_key(char *buff, int read_count, t_display *display)
{
	if (buff[0] == 27)
		map_esc(buff, read_count, display);
	else if (buff[0] == ' ')
		display->items[display->index].selected = -display->items[display->index].selected;
	else if (buff[0] == 127)
	//	delete_current(display);
		delete_item(display, display->index);
	else if (buff[0] == 'k')
		delete_selected(display);
	else if (buff[0] == '\n')
		{restore_tcap();exit(1);}
}*/
