#include "lib/libft.h"
#include <termios.h>
#include <curses.h>
#include <term.h>
#include <termcap.h>
#include <sys/ioctl.h>




typedef	struct		s_item
{
	char  		*text;
	int 		selected;
	size_t		len;
	struct	s_item	*next;
	struct	s_item	*prev;
}			t_item;

typedef	struct	s_display
{
	t_item		**head;
	t_item		*current;
	size_t		count;
	struct	winsize	win_sz;
	unsigned int	lines_wrote;
	int		f_writing;
}		t_display;

extern	t_display	g_display;

int ft_iputchar(int c);
int *ft_static_cursor();
int init_tcap(void);
int restore_tcap(void);
int fill_array(int ac, char **av, t_item items_list[ac]);
t_item	**build_items_list(char **av);
void	set_signals(void);
void	render_display(void);
void	reinit_cursor(void);
void	map_key(char *buff, int read_count);
void	clear_our_mess(void);
