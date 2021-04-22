#include "minishell.h"

t_element	*create_list(void *elt1, void *elt2, size_t data_size,int id)
{
	t_element	*stnode;

	stnode = (t_element *)malloc(sizeof(t_element));
	if (stnode == NULL)
		return (NULL);
	else
	{
		stnode->obj1 = malloc(data_size);
		stnode->obj2 = malloc(data_size);
		stnode->obj1 = elt1;
		stnode->obj2 = elt2;
		stnode->id = id;
		stnode->next = NULL;
	}
	return (stnode);
}

t_element	*add_end(t_element **liste, void *elt1, void *elt2,
					size_t data_size, int id)
{
	t_element	*new;
	t_element	*ptr;

	ptr = *liste;
	new = (t_element *)malloc(sizeof(t_element));
	if (new == NULL)
		return (NULL);
	else
	{
		new->obj1 = malloc(data_size);
		new->obj2 = malloc(data_size);
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
		shell->shell = create_list(var[0], var[1], sizeof(char *),0);
	else
		shell->shell = add_end(&shell->shell, var[0], var[1], sizeof(char *),0);
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
		if (strcmp(list->next->obj1, elm) == 0)
		{
			list->next->id = 1;
			free(list->next->obj2);
			list->next->obj2 = NULL;
			break ;
		}
		list = list->next;
	}
}

void	sort_l(t_element *list)
{
	t_element	*ptr;
	t_element	*ptr2;
	char		*temp;
	char		*temp2;
	int			id;

	ptr = list;
	while (ptr)
	{
		ptr2 = ptr->next;
		while (ptr2)
		{
			if (strcmp(ptr->obj1, ptr2->obj1) > 0)
			{
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
			ptr2 = ptr2->next;
		}
		ptr = ptr->next;
	}
}
