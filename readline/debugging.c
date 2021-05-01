#include "readline.h"

void    ft_prompt()
{
    ft_putstr("ayoub-shell");
	ft_putstr("\033[0;32m");
	ft_putstr("$>");
	ft_putstr("\033[0m");
}