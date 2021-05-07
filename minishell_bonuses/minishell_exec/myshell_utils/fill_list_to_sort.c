#include "minishell.h"

int	len_list(t_args *arg)
{
	t_args	*p;
	int		i;

	p = arg;
	i = 0;
	while (p)
	{
		p = p->next;
		i++;
	}
	return (i);
}

int	len_list_element(t_element *element)
{
	t_element	*p;
	int			i;

	p = element;
	i = 0;
	while (p)
	{
		p = p->next;
		i++;
	}
	return (i);
}

void	filling(t_element **ptr, t_element *list)
{
	t_element	*shell;

	shell = list;
	while (shell != NULL)
	{
		if (*ptr == NULL)
			*ptr = create_list(ft_strdup(shell->obj1),
					ft_strdup(shell->obj2), shell->id);
		else
			*ptr = add_end(ptr, ft_strdup(shell->obj1),
					ft_strdup(shell->obj2), shell->id);
		shell = shell->next;
	}
}

void	ft_swap(t_element	*ptr, t_element	*ptr2)
{
	char		*temp;
	char		*temp2;
	int			id;

	temp = ptr->obj1;
	temp2 = ptr->obj2;
	id = ptr->id;
	ptr->obj1 = ptr2->obj1;
	ptr->obj2 = ptr2->obj2;
	ptr->id = ptr2->id;
	ptr2->obj1 = temp;
	ptr2->obj2 = temp2;
	ptr2->id = id;
}

void	sort_l(t_element *list)
{
	t_element	*ptr;
	t_element	*ptr2;

	ptr = list;
	while (ptr)
	{
		ptr2 = ptr->next;
		while (ptr2)
		{
			if (ft_strcmp(ptr->obj1, ptr2->obj1) > 0)
				ft_swap(ptr, ptr2);
			ptr2 = ptr2->next;
		}
		ptr = ptr->next;
	}
}
