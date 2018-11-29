/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 19:40:10 by ktlili            #+#    #+#             */
/*   Updated: 2018/11/29 17:20:07 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

unsigned int	build_items_list(t_item items[], char **av)
{
	int		i;
	int		j;

	i = 1;
	j = 0;
	while (av[i] != NULL)
	{
		if ((items[j].len = ft_strlen(av[i])) > 0)
		{
			items[j].text = av[i];
			items[j].selected = -1;
			items[j].color = NULL;
			j++;
		}
		i++;
	}
	return (j);
}
