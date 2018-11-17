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

	if (flag)
	{
		tputs(tgetstr("te", NULL), 1, ft_iputchar) ; 
		clear_our_mess();
//		tputs(tgetstr("ve", NULL), 1, ft_iputchar) ; 
		tcsetattr(0, TCSANOW, &save);
	
		return (0);
	}
	term = getenv("TERM");
	if ((term == NULL) || (tgetent(NULL, term) <= 0))
	{
		ft_printf("TERM is null\n");
		return (-1);
	}
//	tputs(tgetstr("vi", NULL), 1, ft_iputchar) ; 
	tputs(tgetstr("ti", NULL), 1, ft_iputchar) ; 
//	tputs(tgoto(tgetstr("cm", NULL), 0, 0), 1, ft_iputchar) ; 
	if (tcgetattr(0, &termios_st) != 0)
		return (-1);
	ft_memcpy(&save, &termios_st, sizeof(struct termios));
	termios_st.c_lflag &= ~(ICANON);
	termios_st.c_lflag &= ~(ECHO);
	termios_st.c_cc[VMIN] = 0; // min chars to read, 0 because we want check our signal var everytime
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
/*
void	delete_current(void)
{
	t_item *save;

	save = g_display.current->next;
	if (g_display.current == *(g_display.head))
		*(g_display.head) = save;
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

void	map_esc(char *buff, int read_count)
{
	if (!ft_strcmp(tgetstr("kD", NULL), buff))
	{
		delete_current();
	} 
	if (read_count == 1)
	{
		restore_tcap();
		exit(1);
	}
	if (!ft_strncmp(buff + 1,"[D", 2))
	{
	}
	else if (!ft_strncmp(buff + 1,"[A",2))
	{
		g_display.current = g_display.current->prev;
	}
	else if (!ft_strncmp(buff + 1,"[C",2))
	{
	}
	else if (!ft_strncmp(buff + 1,"[B",2))
	{
		g_display.current = g_display.current->next;
	}
}


void	map_key(char *buff, int read_count)
{
	if (buff[0] == 27)
		map_esc(buff, read_count);
	else if (buff[0] == ' ')
		g_display.current->selected = -g_display.current->selected;
	else if (buff[0] == 127)
		delete_current();
}
*/
