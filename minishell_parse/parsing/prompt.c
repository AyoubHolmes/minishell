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

void red()
{
	ft_putstr_parse("\033[1;31m");
}

void green()
{
	ft_putstr_parse("\033[0;32m");
}

void reset()
{
	ft_putstr_parse("\033[0m");
}

void prompt(int status)
{
	ft_putstr_parse("ayoub-shell");
	if (status == 0)
		green();
	else
		red();
	ft_putstr_parse("$>");
	reset();
}
