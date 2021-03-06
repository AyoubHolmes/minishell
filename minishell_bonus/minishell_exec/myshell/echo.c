#include "../includes/minishell.h"

int	compare_n(char *str)
{
	int	i;
	int	len;

	len = 0;
	len = ft_strlen(str);
	i = 0;
	if (ft_strcmp(str, "") == 0)
		return (1);
	if (str[i] == '-')
	{
		i++;
		while (str[i] && str[i] == 'n')
			i++;
	}
	if (i == len)
		return (0);
	else
		return (1);
}

void	check_echo_args(t_args *elm, int *n, int out_fd)
{
	t_args	*tmp;
	int		a;

	tmp = elm;
	while (tmp && compare_n(tmp->arg) == 0)
	{
		*n = 1;
		tmp = tmp->next;
	}
	while (tmp)
	{
		ft_putstr(tmp->arg, out_fd);
		tmp = tmp->next;
		if (tmp)
			ft_putstr(" ", out_fd);
	}
}

char	*echo_(t_minishell *shell)
{
	int	n;
	int	i;
	int	len;

	len = 0;
	n = 0;
	check_echo_args(shell->args, &n, shell->out_fd);
	if (n == 0)
		ft_putstr("\n", shell->out_fd);
	return ("");
}
