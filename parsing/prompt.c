#include "minishell.h"
#include "readline.h"
#include <fcntl.h>

void	add_char(int c, t_readline **str)
{
	t_readline	*p;

	if (*str == NULL)
	{
		*str = (t_readline *)malloc(sizeof(t_readline));
		(*str)->c = c;
		(*str)->next = NULL;
	}
	else
	{
		p = *str;
		while (p->next)
			p = p->next;
		p->next = (t_readline *)malloc(sizeof(t_readline));
		p->next->c = c;
		p->next->next = NULL;
		p->next->prev = p;
	}
}

t_readline	*duplicate_readline(t_readline **str)
{
	t_readline	*dup;
	t_readline	*s;

	s = *str;
	dup = NULL;
	while (s)
	{
		add_char(s->c, &dup);
		s = s->next;
	}
	return (dup);
}

void	prompt(int status, int err)
{
	if (status != 0 || err != 0)
		ft_putstr("\033[1;31m", 1);
	else
		ft_putstr("\033[0;32m", 1);
	ft_putstr("minishell", 1);
	ft_putstr("$>", 1);
	ft_putstr("\033[0m", 1);
}
