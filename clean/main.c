/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 10:50:41 by ktlili            #+#    #+#             */
/*   Updated: 2018/11/29 16:59:44 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"
#include <signal.h>

static void		print_usage(void)
{
	write(0, "ft_select: Usage: ft_select [args ..]\n", 38);
}

static int		init_display(t_display *display, int ac, char **av)
{
	display->index = 0;
	if ((ac < 2)
			|| ((display->count = build_items_list(display->items, av)) == 0))
	{
		print_usage();
		return (-1);
	}
	set_colors(display->items, display->count);
	if (ioctl(0, TIOCGWINSZ, &(display->win_sz)) == -1)
		return (-1);
	return (0);
}

static void		display_loop(t_display *display, char *key, int read_ret)
{
	tc_clear();
	if ((g_sigresize) || (g_foreground))
		ioctl(0, TIOCGWINSZ, &(display->win_sz));
	g_foreground = 0;
	g_sigresize = 0;
	if (read_ret > 0)
		map_key(key, display);
	if (display->count == 0)
		restore_exit(NULL);
	render_display(*display);
	ft_bzero(key, 10);
}

int				main(int ac, char **av)
{
	char		key[10];
	int			read_ret;
	t_item		items[ac];
	t_display	display;

	ft_bzero(key, 10);
	display.items = items;
	if (init_display(&display, ac, av) == -1)
		return (-1);
	set_signals();
	init_tcap();
	while (42)
	{
		if (((read_ret = read(0, key, 10)) > 0)
				|| (g_sigresize) || (g_foreground))
			display_loop(&display, key, read_ret);
	}
	restore_tcap();
	return (0);
}
