#include "ft_select.h"

unsigned int	build_items_list(t_item items[], char **av)
{
	int 	i;
	int	j;

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
