#include "../includes/minishell.h"

void	free_args(t_args **args)
{
	t_args	*p;
	t_args	*q;

	p = *args;
	while (p != NULL)
	{
		q = p;
		p = p->next;
		free(q->arg);
		q->arg = NULL;
		free(q);
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
