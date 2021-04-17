#include "minishell.h"

void	fill_dispatcher(t_minishell *shell)
{
	char	*(*command[8])(t_minishell *);;

	command[0] = ft_system;
	command[2] = pwd;
	command[1] = echo;
	command[3] = cd;
	command[4] = export_;
	command[5] = unset;
	command[6] = env_;
	command[7] = exit_;
	command[shell->choice](shell);
}
