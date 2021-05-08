#include"minishell.h"

void	ft_free_var(void *var)
{
	if (var)
	{
		free (var);
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
		free (q->obj1);
		free (q->obj2);
		q->obj1 = NULL;
		q->obj2 = NULL;
		free (q);
		q = NULL;
	}
}

void	free_double_p(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		ft_free_var(str[i]);
		i++;
	}
	ft_free_var(str);
}
