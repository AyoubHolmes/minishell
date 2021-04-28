#include"minishell.h"

void	ft_free_var(void *var)
{
	if(var)
	{
		free(var);
		var = NULL;
	}
}

void	free_element(t_element *list)
{
	t_element	*p;
	t_element	*q;

	p = list;
	while (p != NULL)
	{
	q = p;
	p = p->next;
	free(q->obj1);
	free(q->obj2);
	q->obj1 = NULL;
	q->obj2 = NULL;
	free(q);
	q = NULL;
	}
}