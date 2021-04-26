#include "minishell.h"

char	*unset(t_minishell *shell)
{
	t_args	*tmp;
	t_element *var;
	tmp = shell->args;
	while (tmp)
	{
	//	var = catch_elem(tmp->arg,&shell->shell);
		delete_elem(tmp->arg, shell->shell);
		tmp = tmp->next;
	}
	exit(0);
	return ("");
}
