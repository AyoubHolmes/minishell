#include "readline.h"
#include <fcntl.h>

int	size_of_readline(t_readline *str)
{
	t_readline	*p;
	int			i;

	p = str;
	i = 0;
	while (p)
	{
		p = p->next;
		i++;
	}
	return (i);
}

void	delete_last_readline(t_readline **str)
{
	t_readline	*p;

	if (*str && !(*str)->next)
	{
		free(*str);
		*str = NULL;
	}
	else if (*str && str)
	{
		p = *str;
		while (p->next)
			p = p->next;
		free(p->prev->next);
		p->prev->next = NULL;
	}
}

char	*generate_line(t_readline *str)
{
	char	*s;
	int		size;
	int		i;

	i = 0;
	size = size_of_readline(str);
	s = (char *)malloc(sizeof(char) * size + 1);
	while (i < size)
	{
		s[i] = str->c;
		i++;
		str = str->next;
	}
	s[i] = '\0';
	return (s);
}

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

void 	reset_readline(t_readline *str)
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
