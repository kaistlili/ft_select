#include "ft_select.h"


/*
	we exit:
		map_esc
		signal ctrl c
		no count left

*/
int	switch_tcap(int flag)
{
	char 			*term;
	char 			*imode;
	static 	struct	termios	termios_st;
	static	struct	termios	save;

	term = getenv("TERM");
	if (flag)
	{
		clear_our_mess();
		tputs(tgetstr("ve", NULL), 1, ft_iputchar) ; 
		tcsetattr(0, TCSANOW, &save);
	
		return (0);
	}
	if ((term == NULL) || (tgetent(NULL, term) <= 0))
	{
		ft_printf("TERM is null\n");
		return (-1);
	}
	tputs(tgetstr("vi", NULL), 1, ft_iputchar) ; 
	if (tcgetattr(0, &termios_st) != 0)
		return (-1);
	ft_memcpy(&save, &termios_st, sizeof(struct termios));
	termios_st.c_lflag &= ~(ICANON);
	termios_st.c_lflag &= ~(ECHO);
	termios_st.c_cc[VMIN] = 1;
	termios_st.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSANOW, &termios_st) != 0)
		return (-1);
	return (0);
}


int	init_tcap(void)
{
	return(switch_tcap(0));
}

int	restore_tcap(void)
{
	return(switch_tcap(1));
}


void	map_esc(char buff[2])
{
	if (buff[1] == 0)
	{
		restore_tcap();
		exit(1);
	}
	if (!ft_strncmp(buff,"[D", 2))
	{
	}
	else if (!ft_strncmp(buff,"[A",2))
	{
		g_display.current = g_display.current->prev;
	}
	else if (!ft_strncmp(buff,"[C",2))
	{
	}
	else if (!ft_strncmp(buff,"[B",2))
	{
		g_display.current = g_display.current->next;
	} 
}

void	delete_current(void)
{
	t_item *save;

	save = g_display.current->next;
	if (g_display.current == *(g_display.head))
		g_display.head = &(g_display.current);
	g_display.current->prev->next = g_display.current->next;
	g_display.current->next->prev = g_display.current->prev;
	free(g_display.current);
	g_display.current = save;
	g_display.count = g_display.count - 1;
	if (g_display.count == 0)
	{
		restore_tcap();
		exit(1);
	}
}

void	map_key(char buff[3])
{
	if (buff[0] == 27)
		map_esc(&buff[1]);
	if (buff[0] == ' ')
		g_display.current->selected = -g_display.current->selected;
	if ((buff[0] == 127) || (buff[0] == 8))
		delete_current();
}
