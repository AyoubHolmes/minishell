#include "minishell.h"

char	*env_(t_minishell *shell_)
{
	t_element	*p;

	p = shell_->shell;
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
	close(shell_->out_fd);
	close(shell_->in_fd);
	dup2(shell_->old_stdout, 1);
	dup2(shell_->old_stdin, 0);
	exit(0);
	return ("");
}
