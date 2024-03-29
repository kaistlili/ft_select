#include "lib/libft.h"
#include <termios.h>
#include <curses.h>
#include <term.h>
#include <termcap.h>
#include <sys/ioctl.h>


#define	CREG "\x1B[0m"
#define	CRED "\x1B[31m"
#define CGREEN "\x1B[32m"
#define	CBLUE "\x1B[34m"

typedef	struct		s_item
{
	char  		*text;
	int 		selected;
	size_t		len;
	char		*color;
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

typedef	void (*t_keyaction)(t_display*);

int		ft_iputchar(int c);
int		init_tcap(void);
int		restore_tcap(void);
unsigned int	build_items_list(t_item *items,char **av);
void	set_signals(void);
void	render_display(t_display display);
void	map_key(char *buff, int read_count, t_display *display);
void	clear_our_mess(t_display display);
void	set_cursor(t_display display, unsigned int current, unsigned int *col_len);
//void	restore_exit();
struct	termios	*termios_set(void);
void	signal_dispatcher(int signo);
void	set_colors(t_item *items, unsigned int count);
int		init_win(unsigned int height, unsigned int width);

//i

void	delete_current(t_display *display);
void	delete_item(t_display *display, int index);
void	delete_selected(t_display *display);
void	restore_exit(t_display *display);
void	move_up(t_display *display);
void	move_down(t_display *display);
void	move_left(t_display *display);
void	move_right(t_display *display);
void	select_current(t_display *display);
void	return_selected(t_display *display);
