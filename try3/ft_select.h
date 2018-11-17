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
}			t_item;

typedef	struct	s_display
{
	t_item				*items;
	unsigned	int		count;
	unsigned	int		index;
	struct	winsize		win_sz;
}		t_display;

extern int	g_sigresize;
extern int	g_foreground;


int ft_iputchar(int c);
int *ft_static_cursor();
int init_tcap(void);
int restore_tcap(void);
int fill_array(int ac, char **av, t_item items_list[ac]);
unsigned int	build_items_list(t_item *items,char **av);
void	set_signals(void);
void	render_display(t_display display);
void	reinit_cursor(void);
void	map_key(char *buff, int read_count, t_display *display);
void	clear_our_mess(void);
void	set_cursor(t_display display, int current, unsigned int *col_len);
void	restore_exit();
struct	termios	*termios_set(void);
void	signal_dispatcher(int signo);
