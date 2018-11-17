#include "ft_select.h"

static void	add_to_lst(t_item **head, t_item *new)
{
	t_item *tmp;

	if (*head == NULL)
		*head = new;
	else
	{
		tmp = *head;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
	}
}

t_item	**build_items_list(char **av)
{
	int 	i;
	t_item	**head;
	t_item	*tmp;

	if ((head = malloc(sizeof(t_item*))) == NULL)
		return (NULL);
	*head = NULL;
	i = 1;
	while (av[i] != NULL)
	{
//		if (ft_strlen(av[i]) != 0)
//		{
			g_display.count = g_display.count + 1;
			if ((tmp = malloc(sizeof(t_item))) == NULL)
				return (NULL);
			tmp->text = av[i];
			tmp->len = ft_strlen(av[i]);
			tmp->selected = -1;
			tmp->next = NULL;
			tmp->prev = NULL;
			add_to_lst(head, tmp);
//		}
		i++;
	}
	tmp->next = *head;
	(*head)->prev = tmp;
	return (head);
}
