#include "minishell.h"

char	*exit_(t_minishell *shell)
{
	ft_putstr("exit\n",1);
	exit(0);
	return ("");
}
