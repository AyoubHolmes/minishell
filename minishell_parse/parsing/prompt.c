#include "../../includes/minishell.h"

void	ft_putstr_parse(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
}

void	prompt(int status, int err)
{
	if (status != 0 || err != 0)
		ft_putstr_parse("\033[1;31m");
	else
		ft_putstr_parse("\033[0;32m");
	ft_putstr_parse("minishell");
	ft_putstr_parse("$>");
	ft_putstr_parse("\033[0m");
}
