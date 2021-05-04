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
