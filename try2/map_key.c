#include "ft_select.h"

void	delete_current(t_display *display)
{
	return;
}

void	map_esc(char *buff, int read_count, t_display *display)
{
	if (!ft_strcmp(tgetstr("kD", NULL), buff))
	{
		delete_current(display);
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
		display->items[display->index].selected = 1;
	else if (buff[0] == 127)
		delete_current(display);
}
