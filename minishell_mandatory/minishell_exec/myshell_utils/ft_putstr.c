#include "../includes/minishell.h"

void	ft_putstr(char *str, int fd)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(fd, &str[i], 1);
		i++;
	}
}

char	**identifier_help(char **str)
{
	char	**tmp;

	tmp = ft_split((*str), '=');
	if (tmp[0])
		(*str) = tmp[0];
	else
		(*str) = "\0";
	return (tmp);
}
