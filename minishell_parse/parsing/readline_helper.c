#include "readline.h"

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

char	*clear_trigger(int *status, struct termios *s_termios)
{
	ft_putstr("\n", 1);
	*status = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, s_termios);
	return (ft_strdup("clear"));
}

void	up_trigger(t_history **h, t_readline **dup)
{
	if (*h)
	{
		if ((*h)->prev)
		{
			(*h)->str = *dup;
			*h = (*h)->prev;
			*dup = duplicate_readline(&(*h)->str);
		}
		print_readline(*dup); 
	}
}