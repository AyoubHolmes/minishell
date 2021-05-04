#include "readline.h"

void	down_trigger(t_history **h, t_readline **dup)
{
	if (h)
	{
		if ((*h)->next)
		{
			(*h)->str = *dup;
			*h = (*h)->next;
			*dup = duplicate_readline(&(*h)->str);
		}
		print_readline(*dup); 
	}
}

void	arrow_triggers(int key, t_history **h, t_readline **dup)
{
	char s[30];

	ft_putstr("\033[6n", 1);
	read(0, s, 30);
	ft_putstr(tgoto(tgetstr("cm", NULL), 13, atoi(&s[2])  - 1), 1);
	ft_putstr(tgetstr("cd", NULL), 1);
	if (key == UP_KEY)
		up_trigger(h, dup);
	else
		down_trigger(h, dup);
}

void	ft_readline_helper1(int c, t_history **h, t_readline **dup)
{
	if (c == UP_KEY || c == DOWN_KEY)
		arrow_triggers(c, h, dup);
	else if (c >= 32 && c <= 127)
	{
		write(1, &c, 4);
		add_char(c, dup);
	}
}

void	quit_control(t_history **h, t_readline_vars *vars, int *status)
{
	*h = vars->last;
	ft_putstr("exit\n", 1);
	tcsetattr(STDIN_FILENO, TCSANOW, &vars->s_termios);
	exit(*status);
}

char	*ft_readline(t_history **h, int *status)
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
			backspace_trigger(&vars.dup);
		else if (vars.c == 0x3)
		{
			ft_putstr("\n", 1);
			*status = 1;
			return (NULL);
		}
		else if (vars.c == 0xC)
			return (clear_trigger(status, &vars.s_termios));
		else if (vars.c == 0x4 && !vars.dup)
			quit_control(h, &vars, status);
		else if (vars.c == 10)
			return (enter_trigger(&vars.last, vars.dup, h, &vars.s_termios));
		ft_readline_helper1(vars.c, h, &vars.dup);
	}
	return (NULL);
}
