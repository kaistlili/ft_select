#include "ft_select.h"

int	ft_iputchar(int c)
{
	if (write(1, &c, 1) < 0)
		return (-1);
	return (0);
}
int main()
{
	init_tcap();
	char key[100];

	tputs(tgetstr("sc", NULL), 0, ft_iputchar);
	while (read(0, key, 100) >= 0)
	{
		if (key[0] == 27)
		{
			if (key[2] == 'A')
			{
				tputs(tgetstr("up",NULL),0, ft_iputchar);
				tputs(tgetstr("sr",NULL),0, ft_iputchar);
			}
			else if (key[2] == 'B')
			{write(1, "\n",1);}
	//			tputs(tgetstr("do",NULL),0, ft_iputchar);
		}
		if (key[0] == 'a')
		{
			tputs(tgetstr("rc", NULL), 0, ft_iputchar);
		}
		ft_bzero(key, 100);
	}
}
