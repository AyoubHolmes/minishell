#include "minishell.h"

int		is_number(char *str)
{
	int	i;

	i = 0;
	while(str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

char	*exit_(t_minishell *shell)
{
	char	*nb;

	if(shell->args && shell->args->next)
	{
		if(is_number(shell->args->arg) == 1)
		{
			ft_putstr("bash: exit: too many arguments\n",shell->err_fd);
			shell->status = 1;
			return("");
		}
	}
	if (shell->args)
	{
		if(is_number(shell->args->arg) == 0)
		{
			ft_putstr("bash: exit: ",shell->err_fd);
			ft_putstr(shell->args->arg,shell->err_fd);
			ft_putstr(": numeric argument required\n",shell->err_fd);
			shell->status = 1;
		}
		else
			shell->status = ft_atoi(shell->args->arg);
	}
	else
		shell->status = 0;
	exit(shell->status);
	return ("");
}
