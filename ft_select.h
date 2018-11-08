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
	struct	s_item	*next;
	struct	s_item	*prev;
}			t_item;

typedef	struct	s_display
{
	t_item		**head;
	t_item		*current;
	struct	winsize	win_sz;
	size_t		count;
}		t_display;

extern	t_display	g_display;

int ft_iputchar(int c);
int *ft_static_cursor();
int init_tcap(void);
int restore_tcap(void);
void clear_scr();
void ft_cursor_move(char *move);
int dispatch_arrows(char buff[2], int i_count, int *current_i);
int tc_clear_line();
int update_cursor(int cursor);
int fill_array(int ac, char **av, t_item items_list[ac]);
t_item	**build_items_list(char **av);
void	set_signals(void);
void	render_display(void);
void	reinit_cursor(void);
void	map_key(char buff[3]);
void	clear_our_mess(void);
