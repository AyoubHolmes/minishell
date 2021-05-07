#include "readline.h"
#include "minishell.h"

char	*enter_trigger(t_readline_vars *vars, t_history **h)
{
	ft_putstr("\n", 1);
	vars->last->str = vars->dup;
	*h = vars->last;
	tcsetattr(STDIN_FILENO, TCSANOW, &vars->s_termios);
	if ((*h)->str)
	{
		vars->finale = generate_line(vars->last->str);
		return (vars->finale);
	}
	return (NULL);
}

void	up_trigger(t_history **h, t_readline **dup)
{
	if (*h)
	{
		if ((*h)->prev)
		{
			reset_readline((*h)->str);
			(*h)->str = (*dup);
			*h = (*h)->prev;
			(*dup) = duplicate_readline(&(*h)->str);
		}
		print_readline((*dup));
	}
}

void	down_trigger(t_history **h, t_readline **dup)
{
	if (h)
	{
		if ((*h)->next)
		{
			reset_readline((*h)->str);
			(*h)->str = (*dup);
			*h = (*h)->next;
			(*dup) = duplicate_readline(&(*h)->str);
		}
		print_readline((*dup));
	}
}

void	arrow_triggers(int key, t_history **h, t_readline **dup)
{
	char	s[30];

	ft_putstr("\033[6n", 1);
	read(0, s, 30);
	ft_putstr(tgoto(tgetstr("cm", NULL), 11, atoi(&s[2]) - 1), 1);
	ft_putstr(tgetstr("cd", NULL), 1);
	if (key == UP_KEY)
		up_trigger(h, dup);
	else if (key == DOWN_KEY)
		down_trigger(h, dup);
}

void	ft_readline_helper(int c, t_history **h, t_readline **dup)
{
	if (c == UP_KEY || c == DOWN_KEY)
		arrow_triggers(c, h, dup);
	else if (c >= 32 && c < 127)
	{
		write(1, &c, 4);
		add_char(c, dup);
	}
}
