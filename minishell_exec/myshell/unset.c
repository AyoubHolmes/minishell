#include "minishell.h"

char	*unset(t_minishell *shell)
{
	t_args	*tmp;

	tmp = shell->args;
	while (tmp)
	{
		delete_elem(tmp->arg, shell->shell);
		tmp = tmp->next;
	}
	return ("");
}
