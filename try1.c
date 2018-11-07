#include "ft_select.h"
#include <signal.h>


int	ft_iputchar(int c)
{
	if (write(1, &c, 1) < 0)
		return (-1);
	return (0);
}


void	handler_resize(int x)
{
	struct winsize s;
	static int index = 0;
	int *cursor;

	cursor = ft_static_cursor();
	ft_bzero(&s, sizeof(s));
	ioctl(0, TIOCGWINSZ, &s);
/*	tputs(tgetstr("rc", NULL), 0, ft_iputchar);
	tc_clear_line();
	ft_printf("||cursor %d ws_col %hhu  ws_row %hhu", *cursor, s.ws_col, s.ws_row);*/
}

int main(int ac, char **av)
{
	struct termios term;
	char c;
	char buff[2];
	t_cursor cursor;
	
	init_tcap(&term);
	ft_bzero(&cursor, sizeof(cursor));
	tputs(tgetstr("sc", NULL), 0, ft_iputchar);
	if (signal(SIGWINCH, handler_resize) ==  SIG_ERR)
		ft_printf("error\n");
	write(1, "$> ", 3);
	while (read(0, &c, 1))
	{
		if (c == 27)
		{
			if (read(2, buff, 2) == 2)
				dispatch_key(buff, &cursor);
			else
			{
				cursor.cursor_pos = cursor.cursor_pos + 2;
				cursor.buffer_len = cursor.buffer_len + 2;
				write(1, buff, 2);
			}
		}
		else if (c == '\n')
		{			
			write(1, "\n$> ", 4);
			ft_bzero(&cursor, sizeof(cursor));
		}
		else
		{
			cursor.cursor_pos = cursor.cursor_pos + 1;
			cursor.buffer_len = cursor.buffer_len + 1;
			write(1, &c, 1);
		}
	
	}
	return (1);
}
