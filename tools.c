#include "ft_select.h"

int	init_tcap(struct termios *term_s)
{
	char *term;
	int i;
	char *imode;
	char ap[2047];

	term = getenv("TERM");
	if ((term == NULL) || (tgetent(NULL, term) <= 0))
	{
		ft_printf("TERM is null\n");
		return (-1);
	}
	imode = tgetstr("im", NULL);
	if (imode == NULL)
		ft_printf("no insert mode\n");
	else
		tputs(imode, 1, ft_iputchar);
	if (tcgetattr(0, term_s) != 0)
		return (-1);
	term_s->c_lflag &= ~(ICANON);
	term_s->c_lflag &= ~(ECHO);
	term_s->c_cc[VMIN] = 1;
	term_s->c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSADRAIN, term_s) != 0)
		return (-1);
	return (0);
}


int	dispatch_arrows(char buff[2], int i_count, int *current_i)
{

	if (!ft_strncmp(buff,"[D", 2))
	{
	}
	else if (!ft_strncmp(buff,"[A",2))
	{
		if (*current_i == 0)
			*current_i = i_count - 1;
		else
			*current_i = *current_i - 1;
	}
	else if (!ft_strncmp(buff,"[C",2))
	{
	}
	else if (!ft_strncmp(buff,"[B",2))
	{
		if (*current_i == i_count - 1)
			*current_i = 0;
		else
			*current_i = *current_i + 1;
	} 
}

int	tc_clear_line()
{
	char *cline;

	cline = tgetstr("ce",NULL);
	if (cline == NULL)
		return (-1);
	if (tputs(cline, 1, ft_iputchar) != 0)
		return (-1);
	return (0);
}

