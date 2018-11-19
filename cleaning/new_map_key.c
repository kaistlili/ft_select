#include "ft_select.h"

static char	**init_tckeymap(void)
{
	static	char	*keycaps[8];
	
	keycaps[0] = "\033[A"; //"tgetstr("ku", NULL);
	keycaps[1] = "\033[B"; //tgetstr("kd", NULL);
	keycaps[2] = "\033[D"; //tgetstr("kl", NULL);
	keycaps[3] = "\033[C"; // tgetstr("kr", NULL);
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

static int 	map_tc_key(char *key, int read_count, t_display *display)
{
	static	char	**keycaps = NULL;
	static	t_keyaction	fn_array[8] = {move_up, move_down,
				 move_left, move_right, delete_current, delete_current, delete_current, NULL};
	int					index;

	(void)read_count; // to fix
	if (keycaps == NULL)
		keycaps = init_tckeymap();
	if ((index = ft_cmparray(keycaps, key)) == -1)
		return (-1);
	fn_array[index](display);
	return (0);
		
}

void	map_key(char *key, int read_count, t_display *display)
{
	static	char	*keypress[] 
			= {"\n", " ", "\x1b", "\104", NULL};
	static	t_keyaction	fn_array[5] 
			= {return_selected, select_current, restore_exit, delete_selected, NULL };
	int	index;

	if (map_tc_key(key, read_count, display) == 1)
		return;	
	if ((index = ft_cmparray(keypress, key)) == -1)
		return;
	fn_array[index](display);
}
