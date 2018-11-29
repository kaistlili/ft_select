/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cursor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 14:36:12 by ktlili            #+#    #+#             */
/*   Updated: 2018/11/29 17:15:28 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static	void	reinit_cursor(unsigned int *col_index,
			unsigned int *tot_pad)
{
	*col_index = 0;
	*tot_pad = 0;
	tc_cursor_goto(0, 0);
	return ;
}

void			set_cursor(t_display display, unsigned int current,
			unsigned int *col_len)
{
	unsigned int			ws_row;
	static	unsigned int	tot_pad = 0;
	static	unsigned int	col_index = 0;

	ws_row = display.win_sz.ws_row;
	if (current == display.count)
	{
		reinit_cursor(&col_index, &tot_pad);
		return ;
	}
	if (((current % ws_row) == 0) && (current != 0))
	{
		tot_pad = tot_pad + 2 + col_len[col_index];
		col_index++;
		tc_cursor_goto(tot_pad + ((col_len[col_index] - display.
			items[current].len) / 2), 0);
	}
	else
	{
		if (current != 0)
			tputs("\n", 1, ft_iputchar);
		tc_col_goto(tot_pad + ((col_len[col_index] - display.
			items[current].len) / 2));
	}
}
