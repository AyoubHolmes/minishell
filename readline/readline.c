#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <term.h>
#include <termios.h>
#include <termcap.h>
#include <signal.h>


typedef struct			s_readline
{
	char				c;
	struct s_readline	*next;
}						t_readline;	

typedef struct			s_history
{
	char				*s;
	struct s_history	*next;
	struct s_history	*prev;
}						t_history;

void	add_history(char *s, t_history **str)
{
	t_history *p;

	if (*str == NULL)
	{
		*str = (t_history *)malloc(sizeof(t_history));
		(*str)->s = s;
		(*str)->next = NULL;
		(*str)->prev = NULL;
	}
	else
	{
		p = *str;
		while (p->next)
			p = p->next;
		p->next = (t_history *)malloc(sizeof(t_history));
		p->next->s = s;
		p->next->next = NULL;
		p->next->prev = p;
	}
}

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

struct termios saved_attributes;

void    reset_input_mode (void)
{
  tcsetattr (STDIN_FILENO, TCSANOW, &saved_attributes);
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

void    set_input_mode (void)
{
  struct termios tattr;
  char *name;

  if (!isatty (STDIN_FILENO))
	{
	  fprintf (stderr, "Not a terminal.\n");
	  exit (1);
	}
  tcgetattr (STDIN_FILENO, &saved_attributes);
  atexit (reset_input_mode);
  tcgetattr (STDIN_FILENO, &tattr);
  tattr.c_lflag &= ~(ICANON | ECHO | ISIG);
  tcsetattr (STDIN_FILENO, TCSAFLUSH, &tattr);
}

int init_term()
{
	int ret;
	char *term_type;

	term_type = getenv("TERM");
	if (term_type == NULL)
	{
		printf("TERM NOT SET\n");
		return (-1);
	}
	ret = tgetent(NULL, term_type);
	if (ret == -1)
	{
		printf("NO ACCESS TO TERMCAPS DATABASE\n");
		return(-1);
	}
	if (ret == 0)
	{
		printf("Terminal type %s not found\n", term_type);
		return(-1);
	}
	return(0);
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
	t_history *h;

	finale = "";
	if (init_term() == 0)
	{
		ft_putstr("ayoub-shell$>");
		str = (t_readline *)malloc(sizeof(t_readline));
		str = NULL;
		h = NULL;
		set_input_mode ();
		column_line_counts[0] = tgetnum("co");
		column_line_counts[1] = tgetnum("li");
		while (1)
		{
			c = 0;
			read (STDIN_FILENO, &c, 4);
			if (c == 0x3)
			{
				ft_putstr("test CTRL+C\n");
				ft_putstr("ayoub-shell");
				ft_putstr("\033[0;32m");
				ft_putstr("$>");
				ft_putstr("\033[0m");
				exit(0);
			}
			if (c == 0x4)
			{
				ft_putstr("test CTRL+D\n");
				ft_putstr("ayoub-shell");
				ft_putstr("\033[0;32m");
				ft_putstr("$>");
				ft_putstr("\033[0m");
				exit(0);
			}
			if (c == 10)
			{
				finale = generate_line(str);
				add_history(finale, &h);
				ft_putstr("\ntest here: ");
				ft_putstr(finale);
				ft_putstr("\n");
				free(finale);
				finale = NULL;
				ft_putstr("ayoub-shell");
				ft_putstr("\033[0;32m");
				ft_putstr("$>");
				ft_putstr("\033[0m");
			}
			else if (is_up_or_down(c))
			{
				if (h != NULL)
				{
					ft_putstr("\033[6n");
					read(0, s, 8);
					ft_putstr(tgoto(tgetstr("cm", NULL), 13, atoi(&s[2])  - 1));
					ft_putstr(tgetstr("cd", NULL));
					if (((c >> 16)&0xFF) == 65)
					{
						write(1, "UP: ", 4);
						
						if (h->prev != NULL)
						{
							finale = generate_line(str);
							h = h->prev;
							ft_putstr(h->s);
						}
					}
					else if (((c >> 16)&0xFF) == 66)
					{
						write(1, "DOWN: ", 6);
						
						if (h->next != NULL)
						{
							h = h->prev;
							ft_putstr(h->s);
						}
						else
							ft_putstr(finale);
					}
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
