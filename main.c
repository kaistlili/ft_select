#include "ft_select.h"
#include <signal.h>


int	ft_iputchar(int c)
{
	if (write(1, &c, 1) < 0)
		return (-1);
	return (0);
}


void	handler_resize(int x)
{
	struct winsize s;
	static int index = 0;
	int *cursor;

	cursor = ft_static_cursor();
	ft_bzero(&s, sizeof(s));
	ioctl(0, TIOCGWINSZ, &s);
	/*ft_printf("||cursor %d ws_col %hhu  ws_row %hhu", *cursor, s.ws_col, s.ws_row);*/
}

void	print_lst(t_display *lst)
{
	t_item *start;
	size_t c = 0;

	start = *(lst->head);
	while (c < lst->count)
	{
		ft_printf("%s seclected %d\n",start->text, start->selected);
		start = start->next;
		c++;
	}
}
/*
int	map_key(char key[3],  t_item items_list[], int i_count,int *current_i)
{

	if (key[0] == 27)
		dispatch_arrows(&key[1], i_count, current_i);
	
}

void	print_item(t_item item, int current)
{
	if (selected)
		tputstr(tgetent(""
}

void	render_array(t_item items_list[], int i_count, int current_i)
{
	int i;

	i = 0;
	while (i < i_count)
	{
		print_item(items_list[i], current_i == i ? 1 : 0);
		i++;
	}
}
*/
void	init_display(t_display *display, int ac, char **av)
{	
	display->head = build_items_list(av);
	if (display->head == NULL)
	{
		ft_printf("malloc error\n");
		exit(1);
	}
	display->count = (size_t)ac - 1;
	display->current = *(display->head);
	if (ioctl(0, TIOCGWINSZ, &(display->win_sz)) == -1)
	{
		ft_printf("ioctl request error\n");
		exit(1);
	}
}
int main(int ac, char **av)
{
	struct termios 	term;
	char 		key[3];
	t_display	display;

	if (ac < 2)
		return (0);
	init_display(&display, ac, av);
	ft_printf("size of lst %zu, sizeof term ws_col %d ws_row %d\n", display.count, display.win_sz.ws_col, display.win_sz.ws_row);
	print_lst(&display);
/*	if (signal(SIGWINCH, handler_resize) ==  SIG_ERR)
		ft_printf("error\n");
	init_tcap(&term);
	while (read(0, key, 3))
	{
		map_key(key, items_list, i_count, &current_i);
		render_array(items_list, i_count, current_i);
	}*/
}
