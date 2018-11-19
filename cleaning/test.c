/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 14:26:09 by ktlili            #+#    #+#             */
/*   Updated: 2018/11/19 16:54:49 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int	ft_iputchar(int c)
{
	if (write(1, &c, 1) < 0)
		return (-1);
	return (0);
}

void	clear_sc()
{
	int i = 2;

	tputs(tgetstr("ho", NULL), 1, ft_iputchar);
	while (i)
	{
		tputs(tgetstr("dl", NULL), 1, ft_iputchar);
		i--;
	}	
}

int main(int ac, char **av)
{if (ac == 1)return 1;

	init_tcap();
	int i = 0;
	char buff[100];

	while (read(0, buff, 100) >= 0)
	{
		if (buff[0] == ' ')
		{
			tputs(tgetstr("us", NULL), 1, ft_iputchar);
			ft_printf("%d frame\n", i);
			tputs(tgetstr("ue", NULL), 1, ft_iputchar);
			ft_printf("%s", av[1]);
			i++;
			ft_bzero(buff, 100);
			tputs(tgetstr("ho", NULL), 1, ft_iputchar);
		}
		else if (buff[0] == 'a')
			clear_sc();
			//			clear_our_mess();

	}
}
