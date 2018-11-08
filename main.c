#include "ft_select.h"
#include <signal.h>

t_display	g_display;

int	ft_iputchar(int c)
{
	if (write(1, &c, 1) < 0)
		return (-1);
	return (0);
}

void	print_lst(void)
{
	t_item *start;
	size_t c = 0;

	start = *(g_display.head);
	while (c < g_display.count)
	{
		ft_printf("%s seclected %d\n",start->text, start->selected);
		start = start->next;
		c++;
	}
}

void	init_display(int ac, char **av)
{	
	g_display.head = build_items_list(av);
	if (g_display.head == NULL)
	{
		ft_printf("malloc error\n");
		exit(1);
	}
	g_display.count = (size_t)ac - 1;
	g_display.current = *(g_display.head);
	if (ioctl(0, TIOCGWINSZ, &(g_display.win_sz)) == -1)
	{
		ft_printf("ioctl request error\n");
		exit(1);
	}
}
int main(int ac, char **av)
{
	struct termios 	term;
	char 		key[3];

	if (ac < 2)
		return (0);
	ft_bzero(key, 3);
	init_display(ac, av);
	init_tcap();
	set_signals();
	render_display();
	while (read(0, key, 3))
	{
		clear_our_mess();
		map_key(key);
		render_display();
		ft_bzero(key, 3);
	}
	restore_tcap();
}
