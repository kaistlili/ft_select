/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 14:21:14 by ktlili            #+#    #+#             */
/*   Updated: 2018/11/29 17:18:34 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int		ft_iputchar(int c)
{
	if (write(0, &c, 1) < 0)
		return (-1);
	return (0);
}

void	tc_cursor_goto(int x, int y)
{
	static char *cm = NULL;

	if (cm == NULL)
		cm = tgetstr("cm", NULL);
	tputs(tgoto(cm, x, y), 1, ft_iputchar);
}

void	tc_col_goto(int x)
{
	static char *ch = NULL;

	if (ch == NULL)
		ch = tgetstr("ch", NULL);
	tputs(tgoto(ch, 0, x), 1, ft_iputchar);
}

void	tc_clear(void)
{
	static char *cl = NULL;

	if (!cl)
		cl = tgetstr("cl", NULL);
	tputs(cl, 1, ft_iputchar);
}

void	tc_underline(int ft_switch)
{
	static	char	*us = NULL;
	static	char	*ue = NULL;

	if ((!us) || (!ue))
	{
		us = tgetstr("us", NULL);
		ue = tgetstr("ue", NULL);
	}
	if (ft_switch == TC_ON)
		tputs(us, 1, ft_iputchar);
	else if (ft_switch == TC_OFF)
		tputs(ue, 1, ft_iputchar);
}

void	tc_videorev(int ft_switch)
{
	static	char	*mr = NULL;
	static	char	*me = NULL;

	if ((!mr) || (!me))
	{
		mr = tgetstr("mr", NULL);
		me = tgetstr("me", NULL);
	}
	if (ft_switch == TC_ON)
		tputs(mr, 1, ft_iputchar);
	else if (ft_switch == TC_OFF)
		tputs(me, 1, ft_iputchar);
}
