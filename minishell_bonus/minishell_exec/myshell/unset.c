#include "../includes/minishell.h"

char	*unset(t_minishell *shell)
{
	t_args		*tmp;

	tmp = shell->args;
	while (tmp)
	{
		if (check_identifier(tmp->arg, shell, 0, tmp->arg) == 1)
			delete_elem(tmp->arg, shell->shell);
		tmp = tmp->next;
	}
	return ("");
}
