#include "readline.h"
#include "minishell.h"

char 	*ft_readline(t_history **h)
{
	t_readline_vars	vars;

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
			return (clear_trigger(&vars.s_termios));
		else if (vars.c == 0x3 || (vars.c == 0x4 && !vars.dup))
			return (quit_control(h, &vars));
		else if (vars.c == 10)
			return (enter_trigger(&vars, h));
		ft_readline_helper(vars.c, h, &vars.dup);
	}
	return (NULL);
}
