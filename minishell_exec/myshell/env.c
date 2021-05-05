#include "minishell.h"

char	*env_(t_minishell *shell_)
{
	t_element	*p;

	p = shell_->shell;
	if (shell_->args)
	{
		ft_putstr("env: ", shell_->err_fd);
		ft_putstr(shell_->args->arg, shell_->err_fd);
		ft_putstr(": No such file or directory\n", shell_->err_fd);
		shell_->er_id = 127;
		return ("");
	}
	while (p != NULL)
	{
		if (p->obj2)
		{
			ft_putstr(p->obj1, shell_->out_fd);
			ft_putstr("=", shell_->out_fd);
			ft_putstr(p->obj2, shell_->out_fd);
			ft_putstr("\n", shell_->out_fd);
		}
		p = p->next;
	}
	return ("");
}
