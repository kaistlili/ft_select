#include "ft_select.h"
#include <sys/stat.h>



int	is_dir(char *path)
{
	struct	stat	data;

	if (stat(path, &data) != 0)
		return (0);
	if (S_ISDIR(data.st_mode))
		return (1);
	return (0);
}

void	set_colors(t_item *items, unsigned int count)
{
	size_t i;
	static	char	*colors[10] = {CRED, CGREEN, CBLUE};

	i = 0;
	while (i < count)
	{
		if (is_dir(items[i].text))
			items[i].color = colors[1];
		else
		{
			ft_strrev(items[i].text);
			if (!ft_strncmp(items[i].text, "c.", 2))
				items[i].color = colors[0];
			else if (!ft_strncmp(items[i].text, "h.", 2))
				items[i].color = colors[2];
			ft_strrev(items[i].text);
		}
		i++;
	}
}
