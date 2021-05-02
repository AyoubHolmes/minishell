#include "minishell.h"

void	add_args(t_args *args_, char *cmd)
{
	t_args *p;

	if (args_ == NULL)
	{
		if (!(args_ = (t_args *)malloc(sizeof(t_args))))
			return ;
		args_->arg = cmd;
		args_->next = NULL;
	}
	else
	{
		p = args_;
		while (p->next)
			p = p->next;
		if (!(p->next = (t_args *)malloc(sizeof(t_args))))
			return ;
		p->next->arg = cmd;
		p->next->next = NULL;
	}
}

void	fill_dispatcher(t_minishell *shell)
{
	char	*(*command[8])(t_minishell *);

	check_cli_args(&shell->args);
	command[0] = ft_system;
	command[2] = pwd;
	command[1] = echo_;
	command[3] = cd;
	command[4] = export_;
	command[5] = unset;
	command[6] = env_;
	command[7] = exit_;
	command[shell->choice](shell);
}
