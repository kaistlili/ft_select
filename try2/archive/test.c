#include "ft_select.h"

int main()
{
	char *term = getenv("TERM");
	tgetent(NULL, term);
char *save = tgetstr("kD", NULL);
	ft_printf("%hhd %hhd %hhd\n", save[0], save[1], save[2]);
}
