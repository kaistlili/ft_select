#include "ft_select.h"

#define KRED "\x1B[31m"
#define KBLU "\x1b[34m"




int main(int ac, char **av)
{
	ft_putstr("this should be normal");
	ft_putstr(KRED);
	ft_putstr("this should be red");
}
