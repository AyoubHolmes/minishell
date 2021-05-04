#include "readline.h"

void	print_readline(t_readline *str)
{
	t_readline	*p;

	p = str;
	if (!p)
		write(1, "", 1);
	while (p)
	{
		write(1, &p->c, 1);
		p = p->next;
	}
}

void	reset_readline(t_readline *str)
{
	t_readline	*p;
	t_readline	*q;

	p = str;
	while (p)
	{
		q = p;
		p = p->next;
		free(q);
		q = NULL;
	}
}

int	ft_atoi_readline(char **s)
{
	int	a;

	a = 0;
	while (ft_isdigit(**s))
	{
		a = (a * 10) + (**s - '0');
		(*s)++;
	}
	return (a);
}
