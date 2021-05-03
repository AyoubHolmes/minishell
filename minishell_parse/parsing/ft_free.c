#include "../../includes/minishell.h"

void	ft_free(void *elm)
{
	if (elm)
	{
		free(elm);
		elm = NULL;
	}
}

void	free_args(t_args **args)
{
	t_args	*p;
	t_args	*q;

	p = *args;
	while (p != NULL)
	{
		q = p;
		p = p->next;
		ft_free(q->arg);
		q->arg = NULL;
		ft_free(q);
		q = NULL;
	}
}

void	free_simple_cmd(t_simple_cmd **simple_cmd)
{
	t_simple_cmd	*p;
	t_simple_cmd	*q;

	p = *simple_cmd;
	while (p != NULL)
	{
		q = p;
		p = p->next;
		free_args(&q->args);
		free(q->cmd);
		q->cmd = NULL;
		free(q);
		q = NULL;
	}
}