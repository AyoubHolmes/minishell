#include "readline.h"
#include "../../includes/minishell.h"

int	ft_atoi_readline(char **s)
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
	char	s[30];
	char	*test;
	int		y;

	ft_putstr("\033[6n", 1);
	read(0, s, 30);
	test = &s[2];
	y = ft_atoi_readline(&test);
	test++;
	y = ft_atoi_readline(&(test));
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

char	*clear_trigger(struct termios *s_termios)
{
	ft_putstr("\n", 1);
	g_cli.status = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, s_termios);
	return (ft_strdup("clear"));
}

char	*quit_control(t_history **h, t_readline_vars *vars)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &vars->s_termios);
	if (vars->c == 0x4 && !vars->dup)
	{
		*h = vars->last;
		ft_putstr("exit\n", 1);
		exit(0);
	}
	ft_putstr("\n", 1);
	g_cli.er_id = 1;
	*h = vars->last;
	reset_readline(vars->dup);
	return (NULL);
}
