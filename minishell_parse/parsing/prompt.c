#include "minishell.h"

void ft_putstr_parse(char *s)
{
	int i = 0;
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
}

void prompt(int status)
{
	ft_putstr_parse("ayoub-shell");
	if (status == 0)
		ft_putstr_parse("\033[0;32m");
	else
		ft_putstr_parse("\033[1;31m");
	ft_putstr_parse("$>");
	ft_putstr_parse("\033[0m");
}
