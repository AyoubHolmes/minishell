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

void	termios_config(struct termios *old_attr)
{
	struct termios	new_attr;
	char			*term_type;
	int				ret;

	term_type = getenv("TERM");
	if (term_type == NULL)
		ft_putstr("\r\033[0KTERM must be set (see 'env').\n", 1);
	ret = tgetent(NULL, term_type);
	if (ret < 0)
		ft_putstr("\r\033[0KCould not access to the termcap database..\n", 1);
	if (ret == 0)
		ft_putstr("\r\033[0KIs not defined in termcap database.\n", 1);
	if (tcgetattr(STDIN_FILENO, old_attr) < 0)
		ft_putstr("Error tcgetattr\n", 1);
	new_attr = *old_attr;
	new_attr.c_lflag &= ~(ECHO | ICANON | ISIG);
	if (tcsetattr(STDIN_FILENO, TCSANOW, &new_attr) < 0)
		ft_putstr("\r\033[0KError tcsetattr.\n", 1);
}

void	backspace_trigger(t_readline **dup)
{
	char	s[20];
	char	*test;
	int		x;
	int		y;

	ft_putstr("\033[6n", 1);
	read(0, s, 8);
	test = &s[2];
	x = ft_atoi_readline(&test);
	test++;
	y = ft_atoi_readline(&(test));
	if (y >= 14 && *dup)
	{
		if (y > 14)
		{
			delete_last_readline(dup);
			ft_putstr(tgetstr("le", NULL), 1);
			ft_putstr(tgetstr("cd", NULL), 1);
		}
		else if (y == 14 && *dup)
		{
			free(*dup);
			*dup = NULL;
		}
	}
}

char	*enter_trigger(t_history **last, t_readline *dup, t_history **h, struct termios *s_termios)
{
	char *finale;

	ft_putstr("\n", 1);
	(*last)->str = dup;
	*h = (*last);
	tcsetattr(STDIN_FILENO, TCSANOW, s_termios);
	if ((*h)->str)
	{
		finale = generate_line((*last)->str);
		return (finale);
	}
	return (NULL);
}

char	*ft_readline(t_history **h, int *status)
{
	char s[20];
	int c;
	struct termios s_termios;
	t_history	*last;
	t_readline	*dup;

	add_history(h);
	last = *h;
	(*h)->str = NULL;
	termios_config(&s_termios);
	dup = NULL;
	while (1)
	{
		c = 0;
		read (STDIN_FILENO, &c, 4);
		if (c == 127 && dup)
			backspace_trigger(&dup);
		else if (c == 0x3)
		{
			ft_putstr("\n", 1);
			*status = 1;
			tcsetattr(STDIN_FILENO, TCSANOW, &s_termios);
			return (NULL);
		}
		else if (c == 0xC)
		{
			ft_putstr("\n", 1);
			*status = 0;
			tcsetattr(STDIN_FILENO, TCSANOW, &s_termios);
			return (ft_strdup("clear"));
		}
		else if (c == 0x4)
		{	
			if (!dup)
			{
				*h = last;
				ft_putstr("exit\n", 1);
				tcsetattr(STDIN_FILENO, TCSANOW, &s_termios);
				exit(*status);
			}
		}
		else if (c == 10)
			return (enter_trigger(&last, dup, h, &s_termios));
		else if (c == UP_KEY)
		{
			ft_putstr("\033[6n", 1);
			read(0, s, 30);
			ft_putstr(tgoto(tgetstr("cm", NULL), 13, atoi(&s[2])  - 1), 1);
			ft_putstr(tgetstr("cd", NULL), 1);
			if (*h)
			{
				if ((*h)->prev)
				{
					(*h)->str = dup;
					*h = (*h)->prev;
					dup = duplicate_readline(&(*h)->str);
				}
				print_readline(dup); 
			}
		}
		else if (c == DOWN_KEY)
		{
			ft_putstr("\033[6n", 1);
			read(0, s, 30);
			ft_putstr(tgoto(tgetstr("cm", NULL), 13, atoi(&s[2])  - 1), 1);
			ft_putstr(tgetstr("cd", NULL), 1);
			if (h)
			{
				if ((*h)->next)
				{
					(*h)->str = dup;
					*h = (*h)->next;
					dup = duplicate_readline(&(*h)->str);
				}
				print_readline(dup); 
			}
		}
		else if (c >= 32 && c <= 127)
		{
			write(1, &c, 4);
			add_char(c, &dup);
		}
	}
	return (NULL);
}