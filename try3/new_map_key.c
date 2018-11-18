#include "ft_select.h"

void	delete_item(t_display *display, int index);
void	delete_selected(t_display *display);
void	restore_exit(t_display *display);
void	move_up(t_display *display);
void	move_down(t_display *display);
void	move_left(t_display *display);
void	move_right(t_display *display);
void	select_current(t_display *display);
void	return_selected(t_display *display);


char	**init_keymap(void)
{
	static	char	*keycaps[7];
	
	keycaps[0] = "\033[A"; //"tgetstr("ku", NULL);
	keycaps[1] = "\033[B"; //tgetstr("kd", NULL);
	keycaps[2] = "\033[D"; //tgetstr("kl", NULL);
	keycaps[3] = "\033[C"; // tgetstr("kr", NULL);
	keycaps[4] = tgetstr("kb", NULL);
	keycaps[5] = tgetstr("kD", NULL);
	keycaps[6] = NULL;
	return (keycaps);
}

int	ft_cmparray(char **array, char *str)
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

int 	map_tc_key(char *key, int read_count, t_display *display)
{
	static	char	**keycaps = NULL;
	static	t_keyaction	fn_array[7] = {move_up, move_down,
				 move_left, move_right, delete_current, delete_current, NULL};
	int					index;

	if (keycaps == NULL)
		keycaps = init_keymap();
	if ((index = ft_cmparray(keycaps, key)) == -1)
		return (-1);
	fn_array[index](display);
	return (0);
		
}

void	map_key(char *key, int read_count, t_display *display)
{
	static	char	*keypress[] 
			= {"\n", " ", "\x1b", "\x1b\x5b\x33\x3b\x32\x7e", NULL};
	static	t_keyaction	fn_array[5] 
			= {return_selected, select_current, restore_exit, delete_selected, NULL };
	int	index;

	if (map_tc_key(key, read_count, display) == 1)
		return;	
	if ((index = ft_cmparray(keypress, key)) == -1)
		return;
	fn_array[index](display);
}
