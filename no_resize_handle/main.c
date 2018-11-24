/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 10:50:41 by ktlili            #+#    #+#             */
/*   Updated: 2018/11/23 12:39:03 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (write(0, &c, 1) < 0)
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
	tputs(tgoto(tgetstr("cm", NULL), 0, 0), 1, ft_iputchar);
	if (display->count == 0)
		return (-1);
	if (ioctl(0, TIOCGWINSZ, &(display->win_sz)) == -1)
	{
		ft_printf("ioctl request error\n");
		exit(1);
	}
	return (0);
}

t_display	*g_screen;

int main(int ac, char **av)
{
	char 		key[100];
	int		read_ret;
	t_item		items[ac];
	t_display	display;
	//struct	winsize	win_sz;

	if (ac < 2)
		return (0);
	init_tcap();
	ft_bzero(key, 100);
	display.items = items;
	if (init_display(&display, av) == -1)
		return (0);
	set_colors(items, display.count);
	g_screen = &display;
	set_signals();
	render_display(display);
	while ((read_ret = read(0, key, 100)) >= 0)
	{
		clear_our_mess(display);
		g_foreground = 0;
		map_key(key, read_ret, &display);
		if (display.count == 0)
			restore_exit(NULL);
		render_display(display);
		ft_bzero(key, 100);
	}
	restore_tcap();
}
