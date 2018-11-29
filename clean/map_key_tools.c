/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_key.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 19:40:04 by ktlili            #+#    #+#             */
/*   Updated: 2018/11/29 17:32:15 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	restore_exit(t_display *display)
{
	(void)display;
	restore_tcap();
	exit(1);
}

void	select_current(t_display *display)
{
	display->items[display->index].selected = -display->
		items[display->index].selected;
	move_down(display);
}

void	delete_item(t_display *display, int index)
{
	size_t start;

	start = index + 1;
	while (start < display->count)
	{
		ft_memmove(display->items + start - 1,
			display->items + start, sizeof(t_item));
		start++;
	}
	display->count = display->count - 1;
	if (display->count == 0)
		return ;
	if ((display->index) >= display->count)
		display->index = (display->index) % display->count;
	return ;
}

void	return_selected(t_display *display)
{
	size_t c;
	size_t space;

	restore_tcap();
	c = 0;
	space = 0;
	while (c < display->count)
	{
		if (display->items[c].selected == 1)
		{
			if (space)
				write(1, " ", 1);
			write(1, display->items[c].text, display->items[c].len);
			space = 1;
		}
		c++;
	}
	exit(1);
}

void	delete_selected(t_display *display)
{
	size_t			i;
	unsigned int	save;

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
		return ;
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
		display->index = (display->index
			+ ((display->count / display->win_sz.ws_row)
				* display->win_sz.ws_row));
		if (display->index >= display->count)
			move_left(display);
	}
	else
		display->index = display->index - display->win_sz.ws_row;
}

void	move_right(t_display *display)
{
	if ((display->index + display->win_sz.ws_row) >= display->count)
		display->index = display->index % display->win_sz.ws_row;
	else
		display->index = display->index + display->win_sz.ws_row;
}
