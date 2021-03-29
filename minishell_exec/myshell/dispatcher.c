#include "minishell.h"

char *clear_(t_minishell *shell) 
{
	const char *CLEAR_SCREEN_ANSI = "\e[1;1H\e[2J\n";
  	write(STDOUT_FILENO, CLEAR_SCREEN_ANSI, 12);
	return("");
}

void fill_dispatcher(t_minishell *shell)
{
	char *(*command[9])(t_minishell *);

	if(shell->choice <= 8 && shell->choice >=0)
	{
		command[0] = ft_system;
		command[2] = pwd;
		command[1] = echo;
		command[3] = cd;
		command[4] = export_;
		command[5] = unset;
		command[6] = env_;
		command[7] = exit_;
		command[8] = clear_;
		command[shell->choice](shell);
	}
	else
		ft_putstr(" :command not found\n",1);
}