#include "ft_select.h"

static struct termios	*termios_save(struct termios *termios_st)
{
	static	struct termios	save_termios;

	if (termios_st != NULL)
		ft_memcpy(&save_termios, termios_st, sizeof(struct termios));
	return (&save_termios);
}

static void		undo_caps(void)
{	
	tputs(tgetstr("te", NULL), 1, ft_iputchar);
//	tputs(tgetstr("ve", NULL), 1, ft_iputchar);
}

struct termios	*termios_set(void)
{
	static	struct termios	curr_termios;
	static	int		flag = 1;

	if (flag)
	{
		flag = 0;
		if (tcgetattr(0, &curr_termios) != 0)
		{
			undo_caps();
			exit(1);
		}
		termios_save(&curr_termios);
	}
	return (&curr_termios);
}


int	init_tcap(void)
{
	char 			*term;
	struct	termios	*termios_st;

	if (((term = getenv("TERM")) == NULL) || (tgetent(NULL, term) <= 0))
	{
		ft_printf("term is dumb\n");
		return (-1);
	}
	tputs(tgetstr("ti", NULL), 1, ft_iputchar);
//	tputs(tgetstr("vi", NULL), 1, ft_iputchar);
	termios_st = termios_set();
	termios_st->c_lflag &= ~(ICANON);
	termios_st->c_cc[VMIN] = 1; /*min chars to read */
	termios_st->c_cc[VTIME] = 0;
	termios_st->c_lflag &= ~(ECHO);
	if (tcsetattr(0, TCSANOW, termios_st) != 0)
	{
		undo_caps();
		exit(1);
	}
	PC = 'k';
	/*
	char *up = tgetstr("up", NULL);
	printf("PC %d OSPEED %hd\n", PC, ospeed);
	printf("cap 'up' :%hhd %hhd %hhd %hhd %hhd %hhd %hhd\n",up[0],up[1],up[2],up[3], up[4], up[5], up[6]);
	char *dl = tgetstr("dl", NULL);
	printf("cap 'dl' :%hhd %hhd %hhd %hhd %hhd %hhd %hhd %hhd %hhd\n",dl[0],dl[1],dl[2],dl[3], dl[4], dl[5],dl[6], dl[7], dl[8]);
	while (42){};
*/
	return (0);	
}

int restore_tcap(void)
{
	struct	termios	*save;

	save = termios_save(NULL);
	undo_caps();
	tcsetattr(0, TCSANOW, save);
	return (0);
}
