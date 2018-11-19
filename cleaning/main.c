#include "ft_select.h"
#include <signal.h>

/*
	add shift+del to del all selected
	add left and right to move between cols
	add some colors
	add tty checks
	


*/
int	ft_iputchar(int c)
{
	if (write(1, &c, 1) < 0)
		return (-1);
	return (0);
}

void	print_items(t_display *display)
{
	size_t i;

	i = 0;
	while (i < display->count)
	{
		ft_printf("%s\n", display->items[i].text);
		i++;
	}
}

int	init_display(t_display *display, char **av)
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
	if (init_display(&display, av) == -1)
		return (0);
	set_colors(items, display.count);
	init_tcap();
	set_signals();
	render_display(display);
	while ((read_ret = read(0, key, 100)) >= 0)
	{
		if ((read_ret) || (g_sigresize) || (g_foreground))
		{
			if (ioctl(0, TIOCGWINSZ, &(display.win_sz)) == -1)
				exit(1);
			g_sigresize = 0;
			g_foreground = 0;
			map_key(key, read_ret, &display);
			if (display.count == 0)
				break;
			clear_our_mess();
			render_display(display);
			ft_bzero(key, 100);
		}
	}
	restore_tcap();
}
