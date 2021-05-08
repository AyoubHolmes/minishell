#include "readline.h"

void	add_history(t_history **history)
{
	t_history	*p;

	if (*history == NULL)
	{
		*history = (t_history *)malloc(sizeof(t_history));
		(*history)->str = NULL;
		(*history)->next = NULL;
		(*history)->prev = NULL;
	}
	else if ((*history)->str)
	{
		p = (t_history *)malloc(sizeof(t_history));
		p->str = NULL;
		p->prev = *history;
		p->next = NULL;
		(*history)->next = p;
		*history = p;
	}
}

t_history	*duplicate_history(t_history **history)
{
	t_history	*dup;
	t_history	*p;

	p = *history;
	dup = (t_history *)malloc(sizeof(t_history));
	dup->str = duplicate_readline(&(*history)->str);
	return (dup);
}

t_history	*get_last_history(t_history **str)
{
	t_history	*p;

	p = *str;
	while (p->next)
		p = p->next;
	return (p);
}
