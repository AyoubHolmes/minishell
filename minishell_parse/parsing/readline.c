#include "readline.h"
#include "../../includes/minishell.h"

int		ft_atoi_readline(char **s)
{
	int		a;

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

void	ft_backspace(t_readline **dup)
{
	char s[30];

	ft_putstr("\033[6n", 1);
	read(0, s, 30);
	char *test = &s[2];
	int x = ft_atoi_readline(&test);
	test++;
	int y = ft_atoi_readline(&(test));
	if (y > 12)
	{
		delete_last_readline(dup);
		ft_putstr(tgetstr("le", NULL), 1);
		ft_putstr(tgetstr("cd", NULL), 1);
	}
	else if (y == 12 && *dup)
	{
		free(*dup);
		*dup = NULL;
	}
}

char	*clear_trigger(int *status, struct termios *s_termios)
{
	ft_putstr("\n", 1);
	*status = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, s_termios);
	return (ft_strdup("clear"));
}

void	quit_control(t_history **h, t_readline_vars *vars, int *status)
{
	*h = vars->last;
	ft_putstr("exit\n", 1);
	tcsetattr(STDIN_FILENO, TCSANOW, &vars->s_termios);
	exit(*status);
}


char 	*ft_readline(t_history **h)
{
	t_readline_vars vars;

	add_history(h);
	vars.last = *h;
	(*h)->str = NULL;
	termios_config(&vars.s_termios);
	vars.dup = NULL;
	while (1)
	{
		vars.c = 0;
		read (STDIN_FILENO, &vars.c, 4);
		if (vars.c == 127 && vars.dup)
			ft_backspace(&vars.dup);
		else if (vars.c == 0xC)
			return (clear_trigger(g_cli.status, &vars.s_termios));
		else if (vars.c == 0x3)
		{
			ft_putstr("\n", 1);
			g_cli.er_id = 1;
			*h = vars.last;
			tcsetattr(STDIN_FILENO, TCSANOW, &vars.s_termios);
			return (NULL);
		}
		else if (vars.c == 0x4 && !vars.dup)
			quit_control(h, &vars, g_cli.status);
		else if (vars.c == 10)
		{
			ft_putstr("\n", 1);
			vars.last->str = vars.dup;
			*h = vars.last;
			tcsetattr(STDIN_FILENO, TCSANOW, &vars.s_termios);
			if ((*h)->str)
			{
				vars.finale = generate_line(vars.last->str);
				return (vars.finale);
			}
			return (NULL);
		}
		else if (vars.c == UP_KEY || vars.c == DOWN_KEY)
		{
			ft_putstr("\033[6n", 1);
			read(0, vars.s, 30);
			ft_putstr(tgoto(tgetstr("cm", NULL), 11, atoi(&vars.s[2])  - 1), 1);
			ft_putstr(tgetstr("cd", NULL), 1);
			if (vars.c == UP_KEY)
			{
				if (*h)
				{
					if ((*h)->prev)
					{
						(*h)->str = vars.dup;
						*h = (*h)->prev;
						vars.dup = duplicate_readline(&(*h)->str);
					}
					print_readline(vars.dup); 
				}
			}
			else if (vars.c == DOWN_KEY)
			{
				if (h)
				{
					if ((*h)->next)
					{
						(*h)->str = vars.dup;
						*h = (*h)->next;
						vars.dup = duplicate_readline(&(*h)->str);
					}
					print_readline(vars.dup); 
				}	
			}
		}
		else if (vars.c >= 32 && vars.c < 127)
		{
			write(1, &vars.c, 4);
			add_char(vars.c, &vars.dup);
		}
	}
	return (NULL);
}