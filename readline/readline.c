#include "readline.h"

void	ft_putchar(char s)
{
	write(1, &s, 1);
}

int		is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

int		ft_atoi_readline(char **s)
{
	int		a;

	a = 0;
	while (is_digit(**s))
	{
		a = (a * 10) + (**s - '0');
		(*s)++;
	}
	return (a);
}

void ft_putstr(char *s)
{
	if (s)
	{
		while (*s)
		{
			write(1, s, 1);
			s++;
		}
	}
}

int is_up_or_down(int c)
{
  return ((c&0xFF) == 27 && ((c >> 8)&0xFF) == 91 && ((c >> 24)&0xFF) == 0);
}

void	termios_config(struct termios *old_attr)
{
	struct termios	new_attr;
	char			*term_type;
	int				ret;
	term_type = getenv("TERM");
	if (term_type == NULL)
		ft_putstr("\r\033[0KTERM must be set (see 'env').\n");
	ret = tgetent(NULL, term_type);
	if (ret < 0)
		ft_putstr("\r\033[0KCould not access to the termcap database..\n");
	if (ret == 0)
		ft_putstr("\r\033[0KIs not defined in termcap database.\n");
	if (tcgetattr(STDIN_FILENO, old_attr) < 0)
		ft_putstr("Error tcgetattr\n");
	new_attr = *old_attr;
	new_attr.c_lflag &= ~(ECHO | ICANON | ISIG);
	if (tcsetattr(STDIN_FILENO, TCSANOW, &new_attr) < 0)
		ft_putstr("\r\033[0KError tcsetattr.\n");
}

char 	*ft_readline(t_history **h)
{
	char s[30];
	char *finale;
	int c;
	struct termios s_termios;
	t_history	*last;
	t_history	*dup;

	add_history(h);
	(*h)->str = NULL;
	termios_config(&s_termios);
	while (1)
	{
		c = 0;
		read (STDIN_FILENO, &c, 4);
		if (c == 127 && (*h)->str)
		{
			ft_putstr("\033[6n");
			read(0, s, 8);
			char *test = &s[2];
			int x = ft_atoi_readline(&test);
			test++;
			int y = ft_atoi_readline(&(test));
			if (y > 14)
			{
				delete_last_readline(&(*h)->str);
				ft_putstr(tgetstr("le", NULL));
				ft_putstr(tgetstr("cd", NULL));
			}
			else if (y == 14 && (*h)->str)
			{
				free((*h)->str);
				(*h)->str = NULL;
			}
		}
		else if (c == 0x3)
		{
			ft_putstr("\ntest CTRL+C\n");
			return (NULL);
		}
		else if (c == 0x4)
		{
			ft_putstr("\ntest CTRL+D\n");
			exit(0);
		}
		else if (c == 10)
		{
			last = get_last_history(h);
			last->str = (*h)->str;
			*h = get_last_history(h);;
			if ((*h)->str)
			{
				finale = generate_line(last->str);
				return (finale);
			}
			else
				return (NULL);
		}
		else if (is_up_or_down(c))
		{
			ft_putstr("\033[6n");
			read(0, s, 30);
			ft_putstr(tgoto(tgetstr("cm", NULL), 13, atoi(&s[2])  - 1));
			ft_putstr(tgetstr("cd", NULL));
			if (((c >> 16)&0xFF) == 65) // UP
			{
				if (*h)
				{
					if ((*h)->prev)
						*h = (*h)->prev;
					print_readline((*h)->str); 
				}
			}
			else if (((c >> 16)&0xFF) == 66) // DOWN
			{
				if (h)
				{
					if ((*h)->next)
							*h = (*h)->next;
						print_readline((*h)->str); 
				}	
			}
		}
		else
		{
			write(1, &c, 4);
			add_char(c, &(*h)->str);
		}
	}
	return (NULL);
}


int     main(int argc,char **argv,char **env)
{
	t_history *history;
	char		*tmp;

	history = NULL;
    while(1)
    {
		ft_prompt();
		tmp = ft_readline(&history);
		ft_putstr("\nCommand: ");
		ft_putstr(tmp);
		ft_putstr("\n");
		ft_history_printer(history);
	}
	return (0);
}
