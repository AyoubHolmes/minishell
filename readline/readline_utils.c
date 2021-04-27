#include "readline.h"

void	add_char(char c, t_readline **str)
{
	t_readline *p;

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
	}
}

int		size_of_readline(t_readline *str)
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

void		delete_last_readline(t_readline **str)
{
	t_readline	*p;
	t_readline	*q;

	if (*str != NULL)
	{
		p = *str;
    	q = NULL;
		while (p->next)
		{
			q = p;
			p = p->next;
		}
		// free(p);
		// p = NULL;
		if (q)
			q->next = NULL;
	}
}

char	*generate_line(t_readline *str)
{
	char *s;
	int size;
	int i;

	i = 0;
	size = size_of_readline(str);
	s = (char*)malloc(sizeof(char) * size);
	while (i < size)
	{
		s[i] = str->c;
		i++;
		str = str->next;
	}
	return (s);
}

void	print_readline(t_readline *str)
{
	t_readline  *p;

	p = str;
	while (p)
	{
		write(1, &p->c, 1);
		p = p->next;
	}
}

t_readline	*create_readline(char *s)
{
	t_readline *str;

	if (s)
	{
		while (*s)
		{
			add_char(*s, &str);
			s++;
		}
	}
	return str;
}