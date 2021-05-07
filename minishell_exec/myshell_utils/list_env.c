#include "minishell.h"

t_element	*create_list(void *elt1, void *elt2, int id)
{
	t_element	*stnode;

	stnode = (t_element *)malloc(sizeof(t_element));
	if (stnode == NULL)
		return (NULL);
	else
	{
		stnode->obj1 = elt1;
		stnode->obj2 = elt2;
		stnode->id = id;
		stnode->next = NULL;
	}
	return (stnode);
}

t_element	*add_end(t_element **liste, void *elt1, void *elt2, int id)
{
	t_element	*new;
	t_element	*ptr;

	ptr = *liste;
	new = (t_element *)malloc(sizeof(t_element));
	if (new == NULL)
		return (NULL);
	else
	{
		new->obj1 = elt1;
		new->obj2 = elt2;
		new->id = id;
		new->next = NULL;
	}
	while (ptr->next != NULL)
		ptr = ptr->next;
	ptr->next = new;
	return (*liste);
}

void	fill_list(char **var, t_minishell *shell)
{
	if (shell->shell == NULL)
		shell->shell = create_list(var[0], var[1], 0);
	else
		shell->shell = add_end(&shell->shell, var[0], var[1], 0);
}

void	delete_elem(char *elm, t_element *shell_)
{
	t_element	*list;
	t_element	*p;

	list = shell_;
	if (list == NULL)
		return ;
	while (list->next)
	{
		if (ft_strcmp(list->next->obj1, elm) == 0)
		{
			list->next->id = 1;
			break ;
		}
		list = list->next;
	}
}

void	delete_arg(t_args **args, char *arg)
{
	t_args	*p;
	t_args	*q;
	t_args	*s;
	if ((*args)->next)
		p = (*args)->next;
	q = *args;

	if (*args && ft_strcmp((*args)->arg, arg) == 0)
	{
		t_args *tmp = *args;
		(*args) = (*args)->next;
		if (tmp)
			free(tmp);
	}
	else
	{
		while (p)
		{
			if (ft_strcmp(p->arg, arg) == 0)
			{
				s = p;
				q->next = p->next;
				free(s);
				s = NULL;
				break ;
			}
			q = p;
			p = p->next;
		}
	}
}
