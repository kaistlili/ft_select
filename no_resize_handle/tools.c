/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 14:21:14 by ktlili            #+#    #+#             */
/*   Updated: 2018/11/23 13:36:03 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"
/*
void	clear_our_mess(t_display display)
{(void)display;
	tputs(tgetstr("cl", NULL), 1, ft_iputchar);
}
*/

void	clear_our_mess(t_display display)
{
	unsigned int	to_del;
	static	char	*dl = NULL;

	if (dl == NULL)
		dl = tgetstr("dl", NULL);
	if (display.win_sz.ws_row == 0)
		return;
	to_del = display.count;
	if (display.win_sz.ws_row < display.count)
		to_del  = display.win_sz.ws_row;
	while (to_del)
	{
		tputs(dl, 1, ft_iputchar);
		to_del--;
	}
}

