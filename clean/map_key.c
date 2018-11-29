/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_map_key.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 19:40:07 by ktlili            #+#    #+#             */
/*   Updated: 2018/11/29 17:26:26 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static char	**init_tckeymap(void)
{
	static	char	*keycaps[8];

	keycaps[0] = "\033[A";
	keycaps[1] = "\033[B";
	keycaps[2] = "\033[D";
	keycaps[3] = "\033[C";
	keycaps[4] = "\177";
	keycaps[5] = tgetstr("kD", NULL);
	keycaps[6] = tgetstr("kb", NULL);
	keycaps[7] = NULL;
	return (keycaps);
}

static int	ft_cmparray(char **array, char *str)
{
	int i;

	i = 0;
	while (array[i] != NULL)
	{
		if (!ft_strcmp(array[i], str))
			return (i);
		i++;
	}
	return (-1);
}

static int	map_tc_key(char *key, t_display *display)
{
	static	char		**keycaps = NULL;
	static	t_keyaction	fn_array[8] = {move_up, move_down,
				move_left, move_right, delete_current, delete_current,
					delete_current, NULL};
	int					index;

	if (keycaps == NULL)
		keycaps = init_tckeymap();
	if ((index = ft_cmparray(keycaps, key)) == -1)
		return (-1);
	fn_array[index](display);
	return (0);
}

void		map_key(char *key, t_display *display)
{
	static	char		*keypress[] = {"\n", " ", "\x1b", "\104", NULL};
	static	t_keyaction	fn_array[5] = {return_selected,
					select_current, restore_exit, delete_selected, NULL };
	int					index;

	if (map_tc_key(key, display) == 1)
		return ;
	if ((index = ft_cmparray(keypress, key)) == -1)
		return ;
	fn_array[index](display);
}
