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
