#include "ft_select.h"
#include <signal.h>


int	ft_iputchar(int c)
{
	if (write(1, &c, 1) < 0)
		return (-1);
	return (0);
}

void	print_items(t_display *display)
{
	int i;

	i = 0;
	while (i < display->count)
	{
		ft_printf("%s\n", display->items[i].text);
		i++;
	}
}

int	init_display(t_display *display, int ac, char **av)
{
	display->index = 0;
	display->count = build_items_list(display->items, av);
	if (display->count == 0)
		return (-1);
	if (ioctl(0, TIOCGWINSZ, &(display->win_sz)) == -1)
	{
		ft_printf("ioctl request error\n");
		exit(1);
	}
	return (0);
}

void	clear_mess(int count)
{
	while (count > 1)
	{
		tputs(tgetstr("dl",NULL),0, ft_iputchar);
		count--;
	}
}
int main(int ac, char **av)
{
	char 		key[100];
	int		read_ret;
	t_item		items[ac];
	t_display	display;

	if (ac < 2)
		return (0);
	ft_bzero(key, 100);
	display.items = items;
	if (init_display(&display, ac, av) == -1)
		return (0);
//	ft_printf("ws_col %u ws_row %u index at %u\n", display.win_sz.ws_col, display.win_sz.ws_row, display.index);
//	print_items(&display);
	init_tcap();
	set_signals();
	render_display(display);
	while ((read_ret = read(0, key, 100)) >= 0)
	{
		if ((read_ret != 0) || (g_sigresize == 1))
		{
	//		clear_mess(display.count % display.win_sz.ws_row);
			if (ioctl(0, TIOCGWINSZ, &(display.win_sz)) == -1)
				exit(1);
			g_sigresize = 0;
			//clear_our_mess();
			map_key(key, read_ret, &display);
			render_display(display);
			ft_bzero(key, 100);
		}
	}
	restore_tcap();
}
