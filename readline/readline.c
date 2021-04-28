#include "readline.h"

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

int main(int argc, char const *argv[])
{
	int column_line_counts[2];
	char s[8];
	char *finale;
	int c;
	t_readline *str;
	t_readline *str2;
	t_history *h;

	if (init_term() == 0)
	{
		str = NULL;
		str2 = NULL;
		finale = "";
		h = NULL;
		set_input_mode ();
		column_line_counts[0] = tgetnum("co");
		column_line_counts[1] = tgetnum("li");
		ft_prompt();
		while (1)
		{
			c = 0;
			read (STDIN_FILENO, &c, 4);
			if (c == 0x3)
			{
				ft_putstr("\ntest CTRL+C\n");
				exit(0);
			}
			else if (c == 0x4)
			{
				ft_putstr("\ntest CTRL+D\n");
				exit(0);
			}
			else if (c == 10)
			{
				finale = generate_line(str);
				add_history(finale, &h);
				ft_putstr("\ntest here: ");
				ft_putstr(finale);
				ft_putstr("\n");
				str = reset_readline(str);
				ft_prompt();
			}
			else if (c == 127 && str)
			{
				ft_putstr("\033[6n");
				read(0, s, 8);
				char *test = &s[2];
				int x = ft_atoi_readline(&test);
				test++;
				int y = ft_atoi_readline(&(test));
				if (str && y > 14)
				{
					ft_putstr(tgetstr("le", NULL));
					ft_putstr(tgetstr("cd", NULL));
					delete_last_readline(&str);
				}
			}
			else if (is_up_or_down(c))
			{
				ft_putstr("\033[6n");
				read(0, s, 8);
				ft_putstr(tgoto(tgetstr("cm", NULL), 13, atoi(&s[2])  - 1));
				ft_putstr(tgetstr("cd", NULL));
				if (((c >> 16)&0xFF) == 65)
				{
					if (h)
					{
						write(1, "UP: ", 4);
						if (!h->next)
							h = h->prev;
						ft_putstr(h->s);
						if (h->prev)
							h = h->prev;
					}
				}
				else if (((c >> 16)&0xFF) == 66)
				{
					 if (h)
					{
					write(1, "DOWN: ", 6);
						if (h->next)
							h = h->next;
						ft_putstr(h->s);
					}
					else
						print_readline(str); 
				}
			}
			else
			{
				write(1, &c, 4);
				add_char(c, &str);
			}
		}
	}
	return 0;
}
