#include "minishell.h"

char	*exit_(t_minishell *shell)
{
	char *nb;
	if(shell->simple_cmd->args)
		nb = shell->simple_cmd->args->arg;
	else
		nb = "0";
	exit(atoi(nb));
	return (nb);
}
